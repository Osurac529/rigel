#include <array>
#include <chrono>
#include <iostream>
#include <string_view>
#include <thread>

#include "rigel/application.hpp"
#include "rigel/math/math.hpp"
#include "rigel/mesh/geometry_builder.hpp"
#include "rigel/mesh/mesh.hpp"

using namespace rigel;
using namespace webgpu;

int main() {
  try {
    Application application;

    auto &device = application.device();
    auto queue = device.GetQueue();

    const auto mesh = mesh::GeometryBuilder::BuildCube();
    mesh.Validate();

    Buffer vertex_buffer(
        device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex,
        mesh.positions().size() * sizeof(math::vec3f));
    queue.WriteBuffer(vertex_buffer, mesh.positions().data());

    const auto index_count = static_cast<std::uint32_t>(mesh.indices().size());
    Buffer index_buffer(
        device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index,
        mesh.indices().size() * sizeof(std::uint16_t));
    queue.WriteBuffer(index_buffer, mesh.indices().data());

    float time = 0;
    // uniform buffers must be aligned to 16 bytes
    Buffer uniform_buffer(
        device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform, sizeof(math::mat4x4f) * 2);

    const WGPUTextureFormat depthTextureFormat = WGPUTextureFormat_Depth24Plus;

    auto depth_texture =
        TextureBuilder()
            .AddViewFormat(depthTextureFormat)
            .SetSize({application.window().GetWidth(), application.window().GetHeight(), 1})
            .SetUsage(WGPUTextureUsage_RenderAttachment)
            .SetFormat(depthTextureFormat)
            .Build(device);

    auto depth_view =
        TextureViewBuilder().SetAspect(WGPUTextureAspect_DepthOnly).Build(depth_texture);

    ShaderModule shader(device, std::filesystem::path("shaders/shader1.wgsl"));

    auto bind_group_layout =
        BindGroupLayoutBuilder()
            .AddLayoutEntry(
                BindGroupLayoutEntryBuilder()
                    .SetBinding(0)
                    .SetVisibility(WGPUShaderStage_Vertex)
                    .SetBufferBindingLayout(WGPUBufferBindingType_Uniform, uniform_buffer.GetSize())
                    .Build())
            .Build(device);

    auto bind_group = BindGroupBuilder()
                          .AddBinding(
                              BindingBuilder()
                                  .SetBinding(0)
                                  .SetBuffer(uniform_buffer, uniform_buffer.GetSize())
                                  .Build())
                          .SetLayout(bind_group_layout)
                          .Build(device);

    auto pipeline =
        RenderPipelineBuilder()
            .SetLayout(PipelineLayoutBuilder().AddBindGroupLayout(bind_group_layout).Build(device))
            .SetDepthStencilState(DepthStencilStateBuilder().SetFormat(depthTextureFormat).Build())
            .SetFragmentState(
                FragmentStateBuilder()
                    .AddColorTarget(
                        ColorTargetStateBuilder()
                            .SetTextureFormat(application.GetCurrentTexture().GetFormat())
                            .Build())
                    .SetShader(shader, "fs_main")
                    .Build())
            .SetVertexState(
                VertexStateBuilder()
                    .AddVertexBufferLayout(
                        VertexBufferLayoutBuilder()
                            .SetStride(3 * sizeof(float))
                            .AddAttribute(WGPUVertexFormat_Float32x3, 0, 0)
                            //.AddAttribute(WGPUVertexFormat_Float32x3, 8, 1)
                            .Build())
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
      math::mat4x4f transform_matrix = math::mat4x4f(angle, math::mat4x4f::MakeXRotation::Tag) *
                                       math::mat4x4f(angle, math::mat4x4f::MakeYRotation::Tag) *
                                       math::mat4x4f(angle, math::mat4x4f::MakeZRotation::Tag);

      // std::cout << "camera_matrix:\n" << camera_matrix << std::endl;
      // std::cout << "projection_matrix:\n" << projection_matrix << std::endl;
      // std::cout << "world_to_projection:\n" << world_to_projection << std::endl;

      queue.WriteBuffer(uniform_buffer, &world_to_projection);
      queue.WriteBuffer(
          uniform_buffer, &transform_matrix, sizeof(transform_matrix), sizeof(world_to_projection));

      application.PollEvents(
          [](const int key, const float, const float) { std::cout << key << std::endl; });

      auto texture = application.GetCurrentTexture();
      auto texture_view = TextureViewBuilder().Build(texture);

      CommandEncoder command_encoder(device);

      auto render_pass = RenderPassEncoderBuilder()
                             .SetDepthStencilAttachment(
                                 RenderPassDepthStencilAttachmentBuilder()
                                     .SetView(depth_view)
                                     .SetDepthClearValue(1.0f)
                                     .Build())
                             .AddRenderPassColorAttachment(
                                 RenderPassColorAttachmentBuilder()
                                     .SetView(texture_view)
                                     .SetClearValue(WGPUColor{1.0, 0.0, 0.0, 1.0})
                                     .Build())
                             .Build(command_encoder);

      render_pass.SetPipeline(pipeline);
      render_pass.SetIndexBuffer(index_buffer, WGPUIndexFormat_Uint16, 0, index_buffer.GetSize());
      render_pass.SetVertexBuffer(0, vertex_buffer, 0, vertex_buffer.GetSize());
      render_pass.SetBindGroup(0, bind_group);
      render_pass.DrawIndexed(index_count, 1, 0, 0, 0);
      render_pass.End();

      auto command_buffer = command_encoder.Finish();

      device.GetQueue().Submit(command_buffer);

      if (WGPUStatus_Success != application.Present()) {
        std::cout << "failed present" << std::endl;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(16));

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
