#include <iostream>

#include "graphics/graphics.hpp"

int main() {
  try {
    rigel::graphics::Application application;

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

      rigel::graphics::TextureView texture_view(texture, texture_view_descriptor);

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

      auto render_pass = command_encoder.BeginRenderPass(render_pass_descriptor);
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
