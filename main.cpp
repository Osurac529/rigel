#include <iostream>
#include <string_view>

#include "graphics/graphics.hpp"

using namespace rigel::graphics;

constexpr std::string_view shader_source = R"(
@vertex
fn vs_main(@location(0) in_vertex_position: vec2f) -> @builtin(position) vec4f {
    return vec4f(in_vertex_position, 0.0, 1.0);
}

@fragment
fn fs_main() -> @location(0) vec4f {
    return vec4f(0.0, 0.4, 1.0, 1.0);
}
)";

const std::vector<float> vertex_data = {
    // Define a first triangle:
    -0.5, -0.5, +0.5, -0.5, +0.0, +0.5,

    // Add a second triangle:
    -0.55f, -0.5, -0.05f, +0.5, -0.55f, +0.5};

const auto vertex_count = static_cast<uint32_t>(vertex_data.size() / 2);

int main() {
  try {
    Application application;

    auto &device = application.device();
    auto queue = device.GetQueue();

    WGPUBufferDescriptor buffer_descriptor = WGPU_BUFFER_DESCRIPTOR_INIT;
    buffer_descriptor.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
    buffer_descriptor.size = vertex_data.size() * sizeof(float);

    Buffer vertex_buffer(device, buffer_descriptor);
    queue.WriteBuffer(vertex_buffer, 0, vertex_data.data(), buffer_descriptor.size);

    while (application.IsRunning()) {
      application.PollEvents(
          [](const int key, const float, const float) { std::cout << key << std::endl; });

      auto texture = application.GetCurrentTexture();

      WGPUTextureViewDescriptor texture_view_descriptor = WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT;
      texture_view_descriptor.format = texture.GetFormat();
      texture_view_descriptor.dimension = WGPUTextureViewDimension_2D;
      texture_view_descriptor.baseMipLevel = 0;
      texture_view_descriptor.mipLevelCount = 1;
      texture_view_descriptor.baseArrayLayer = 0;
      texture_view_descriptor.arrayLayerCount = 1;
      texture_view_descriptor.aspect = WGPUTextureAspect_All;

      TextureView texture_view(texture, texture_view_descriptor);

      WGPUCommandEncoderDescriptor command_encoder_descriptor =
          WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT;
      auto command_encoder = device.CreateCommandEncoder(command_encoder_descriptor);

      WGPURenderPassColorAttachment render_pass_color_attachment =
          WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
      render_pass_color_attachment.view = texture_view.native();
      render_pass_color_attachment.loadOp = WGPULoadOp_Clear;
      render_pass_color_attachment.storeOp = WGPUStoreOp_Store;
      render_pass_color_attachment.clearValue = WGPUColor{1.0, 0.0, 0.0, 1.0};

      WGPURenderPassDescriptor render_pass_descriptor = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
      render_pass_descriptor.colorAttachmentCount = 1;
      render_pass_descriptor.colorAttachments = &render_pass_color_attachment;

      auto pipeline =
          RenderPipelineBuilder()
              .SetFragmentState(
                  FragmentStateBuilder()
                      .AddColorTarget(
                          ColorTargetStateBuilder().SetTextureFormat(texture.GetFormat()).Build())
                      .SetShader(ShaderModule(device, shader_source), "fs_main")
                      .Build())
              .SetVertexState(
                  VertexStateBuilder()
                      .AddVertexBufferLayout(
                          VertexBufferLayoutBuilder()
                              .SetStride(2 * sizeof(float))
                              .AddAttribute(WGPUVertexFormat_Float32x2, 0, 0)
                              .Build())
                      .SetShader(ShaderModule(device, shader_source), "vs_main")
                      .Build())
              .Build(device);

      auto render_pass = command_encoder.BeginRenderPass(render_pass_descriptor);
      render_pass.SetPipeline(pipeline);
      render_pass.SetVertexBuffer(0, vertex_buffer, 0, vertex_buffer.GetSize());
      render_pass.Draw(vertex_count, 1, 0, 0);
      render_pass.End();

      auto command_buffer = command_encoder.Finish();

      device.GetQueue().Submit(command_buffer);

      if (WGPUStatus_Success != application.Present()) {
        std::cout << "failed present" << std::endl;
      }
    }
  } catch (const std::exception &exception) {
    std::cout << "Exception: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
