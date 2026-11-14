#include <iostream>
#include <string_view>

#include "graphics/graphics.hpp"

using namespace rigel::graphics;

constexpr std::string_view shader_source = R"(
@vertex
fn vs_main(@builtin(vertex_index) in_vertex_index: u32) -> @builtin(position) vec4f {
    var p = vec2f(0.0, 0.0);
    if (in_vertex_index == 0u) {
        p = vec2f(-0.5, -0.5);
    } else if (in_vertex_index == 1u) {
        p = vec2f(0.5, -0.5);
    } else {
        p = vec2f(0.0, 0.5);
    }
    return vec4f(p, 0.0, 1.0);
}

@fragment
fn fs_main() -> @location(0) vec4f {
    return vec4f(0.0, 0.4, 1.0, 1.0);
}
)";

int main() {
  try {
    Application application;

    auto &device = application.device();
    auto queue = device.GetQueue();

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
              .SetVertexShader(ShaderModule(device, shader_source), "vs_main")
              .Build(device);

      auto render_pass = command_encoder.BeginRenderPass(render_pass_descriptor);
      render_pass.SetPipeline(pipeline);
      render_pass.Draw(3, 1, 0, 0);
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
