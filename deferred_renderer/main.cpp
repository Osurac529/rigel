#include <array>
#include <chrono>
#include <iostream>
#include <string_view>
#include <thread>

#include "generated/global_uniforms.hpp"
#include "rigel/rigel.hpp"

using namespace rigel;
using namespace webgpu;

int main() {
  try {
    Application application;

    auto &device = application.device();
    auto queue = device.GetQueue();

    const auto image_checker_board = image::ImageBuilder::BuildCheckerBoard(1024, 1024, 64);
    image_checker_board.Write("checker_board.ppm");
    const auto texture_checker_board = graphics::Texture2DBuilder()
                                           .SetUsage(WGPUTextureUsage_TextureBinding)
                                           .Build(device, image_checker_board);
    const auto texture_view_checker_board = texture_checker_board.View();
    const auto sampler = SamplerBuilder().Build(device);

    const auto mesh = mesh::GeometryBuilder::BuildCube({.texture_coordinates = true});
    mesh.Validate();

    const auto vertex_buffer = graphics::VertexBufferBuilder().Add(mesh).Build(device);
    const auto index_buffer = graphics::IndexBufferBuilder().Add(mesh).Build(device);

    float time = 0;
    generated::global_uniforms uniform_buffer(device);

    graphics::RenderTargets render_targets;
    render_targets.AddColorTarget(
        graphics::ColorRenderTarget(application.GetCurrentTexture().GetFormat())
            .SetClearValue(WGPUColor{1.0, 0.0, 0.0, 1.0}));
    render_targets.SetDepthStencilTarget(
        graphics::DepthStencilRenderTarget(
            device, WGPUTextureFormat_Depth24Plus, application.window().GetWidth(),
            application.window().GetHeight())
            .SetDepthClearValue(1.0f));

    application.SetOnResize(
        [&device, &render_targets](const std::uint32_t width, const std::uint32_t height) {
          render_targets.GetDepthStencilTarget().Resize(device, width, height);
        });

    ShaderModule shader(device, std::filesystem::path("shaders/shader1.wgsl"));

    auto bind_group_layout =
        BindGroupLayoutBuilder()
            .AddLayoutEntry(
                BindGroupLayoutEntryBuilder()
                    .SetBinding(0)
                    .SetVisibility(WGPUShaderStage_Vertex)
                    .SetBufferBindingLayout(
                        WGPUBufferBindingType_Uniform, uniform_buffer.buffer().GetSize())
                    .Build())
            .AddLayoutEntry(
                BindGroupLayoutEntryBuilder()
                    .SetBinding(1)
                    .SetVisibility(WGPUShaderStage_Fragment)
                    .SetTextureBindingLayout(WGPUTextureSampleType_Float)
                    .Build())
            .AddLayoutEntry(
                BindGroupLayoutEntryBuilder()
                    .SetBinding(2)
                    .SetVisibility(WGPUShaderStage_Fragment)
                    .SetSamplerBindingLayout(WGPUSamplerBindingType_Filtering)
                    .Build())
            .Build(device);

    auto bind_group =
        BindGroupBuilder()
            .AddBinding(
                BindingBuilder()
                    .SetBinding(0)
                    .SetBuffer(uniform_buffer.buffer(), uniform_buffer.buffer().GetSize())
                    .Build())
            .AddBinding(
                BindingBuilder().SetBinding(1).SetTextureView(texture_view_checker_board).Build())
            .AddBinding(BindingBuilder().SetBinding(2).SetSampler(sampler).Build())
            .SetLayout(bind_group_layout)
            .Build(device);

    auto pipeline =
        RenderPipelineBuilder()
            .SetFrontFace(WGPUFrontFace_CW)
            .SetCullMode(WGPUCullMode_Back)
            .SetLayout(PipelineLayoutBuilder().AddBindGroupLayout(bind_group_layout).Build(device))
            .SetDepthStencilState(render_targets.GetDepthStencilTarget().state())
            .SetFragmentState(
                FragmentStateBuilder()
                    .AddColorTarget(render_targets.GetColorTarget(0).state())
                    .SetShader(shader, "fs_main")
                    .Build())
            .SetVertexState(
                VertexStateBuilder()
                    .AddVertexBufferLayout(vertex_buffer.layout)
                    .SetShader(shader, "vs_main")
                    .Build())
            .Build(device);

    float angle = 0;
    std::uint32_t frame_count = 0;
    auto last_time = std::chrono::steady_clock::now();

    while (application.IsRunning()) {
      ++time;
      angle += 0.01f;

      math::mat4x4 camera_matrix(math::vec3f(0, 0, -3), math::vec3f(0, 0, 0), math::vec3f(0, 1, 0));
      math::mat4x4f projection_matrix(
          math::ToRadians(60.0f),
          static_cast<float>(application.window().GetWidth()) / application.window().GetHeight(),
          0.1f, 10'000.0f);
      math::mat4x4f world_to_projection = projection_matrix * camera_matrix;
      math::mat4x4f transform_matrix = math::mat4x4f(math::MakeXRotation, angle) *
                                       math::mat4x4f(math::MakeYRotation, angle) *
                                       math::mat4x4f(math::MakeZRotation, angle);

      uniform_buffer.world_to_camera(queue, camera_matrix);
      uniform_buffer.camera_to_projection(queue, projection_matrix);
      uniform_buffer.transform_matrix(queue, transform_matrix);

      application.PollEvents(
          [](const int key, const float, const float) { std::cout << key << std::endl; });

      auto texture = application.GetCurrentTexture();
      auto texture_view = TextureViewBuilder().Build(texture);
      render_targets.GetColorTarget(0).SetWeakView(texture_view);

      CommandEncoder command_encoder(device);

      auto render_pass =
          RenderPassEncoderBuilder()
              .SetDepthStencilAttachment(render_targets.GetDepthStencilTarget().attachment())
              .AddRenderPassColorAttachment(render_targets.GetColorTarget(0).attachment())
              .Build(command_encoder);

      render_pass.SetPipeline(pipeline);
      render_pass.SetBindGroup(0, bind_group);
      render_pass.SetIndexBuffer(index_buffer.buffer, index_buffer.format);
      render_pass.SetVertexBuffer(0, vertex_buffer.buffer);
      render_pass.DrawIndexed(mesh.GetIndexCount(), 1, 0, 0, 0);
      render_pass.End();

      auto command_buffer = command_encoder.Finish();

      device.GetQueue().Submit(command_buffer);

      if (WGPUStatus_Success != application.Present()) {
        std::cout << "failed present" << std::endl;
      }

      const auto now = std::chrono::steady_clock::now();
      std::chrono::duration<double> elapsed_seconds = now - last_time;

      if (elapsed_seconds.count() >= 1) {
        last_time = now;
        std::cout << frame_count / elapsed_seconds.count() << std::endl;
        frame_count = 0;
      }

      ++frame_count;
    }
  } catch (const std::exception &exception) {
    std::cout << "Exception: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
