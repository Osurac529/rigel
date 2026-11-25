#include <array>
#include <chrono>
#include <iostream>
#include <string_view>
#include <thread>

#include "rigel/generated/deferred_shaderper_draw_uniforms.hpp"
#include "rigel/rigel.hpp"

using namespace rigel;
using namespace webgpu;

int main() {
  try {
    WGPULimits device_limits = WGPU_LIMITS_INIT;
    // todo: Get this from DeferredRender statically
    device_limits.maxColorAttachmentBytesPerSample = 36;
    Application application({.device_limits = device_limits});

    auto &device = application.device();
    auto queue = device.GetQueue();

    const auto image_checker_board = image::ImageBuilder::BuildCheckerBoard(1024, 1024, 64);
    image_checker_board.Write("checker_board.ppm");
    const auto texture_checker_board = graphics::Texture2DBuilder()
                                           .SetUsage(WGPUTextureUsage_TextureBinding)
                                           .Build(device, image_checker_board);
    const auto texture_view_checker_board = texture_checker_board.View();
    const auto sampler = SamplerBuilder().Build(device);

    const auto mesh = mesh::GeometryBuilder::BuildCube(
        {.texture_coordinates = true, .normals = true, .tangents = true});
    mesh.Validate();

    const auto vertex_buffer = graphics::VertexBufferBuilder().Add(mesh).Build(device);
    const auto index_buffer = graphics::IndexBufferBuilder().Add(mesh).Build(device);

    float time = 0;
    graphics::DeferredRenderer deferred_renderer(
        device, {vertex_buffer.layout}, application.window().GetWidth(),
        application.window().GetHeight());

    generated::per_draw_uniforms per_draw_uniforms(device);

    const auto per_draw_bind_group = webgpu::BindGroupBuilder()
                                         .AddBinding(
                                             webgpu::BindingBuilder()
                                                 .SetBinding(0)
                                                 .SetBuffer(per_draw_uniforms.buffer())
                                                 .Build())
                                         .SetLayout(deferred_renderer.per_draw_bind_group_layout())
                                         .Build(device);

    application.SetOnResize(
        [&device, &deferred_renderer](const std::uint32_t width, const std::uint32_t height) {
          deferred_renderer.Resize(device, width, height);
        });

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

      deferred_renderer.SetWorldToCamera(queue, camera_matrix);
      deferred_renderer.SetCameraToProjection(queue, camera_matrix);
      per_draw_uniforms.local_to_world(queue, transform_matrix);
      per_draw_uniforms.normal_transform(
          queue, math::mat3x3f(transform_matrix).Transpose().Inverse());

      application.PollEvents(
          [](const int key, const float, const float) { std::cout << key << std::endl; });

      auto texture = application.GetCurrentTexture();
      auto texture_view = TextureViewBuilder().Build(texture);

      CommandEncoder command_encoder(device);

      auto render_pass = deferred_renderer.CreateRenderPassEncoder(command_encoder);

      render_pass.SetIndexBuffer(index_buffer.buffer, index_buffer.format);
      render_pass.SetVertexBuffer(0, vertex_buffer.buffer);
      // render_pass.SetBindGroup(1, material.bind_group());
      render_pass.SetBindGroup(2, per_draw_bind_group);
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
