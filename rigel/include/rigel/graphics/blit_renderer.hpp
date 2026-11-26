#pragma once

#include "rigel/graphics/render_targets.hpp"

namespace rigel::graphics {

// class BlitRenderer {
// public:
//   explicit BlitRenderer(const webgpu::Device &device, std::uint32_t width, std::uint32_t height);
//
//   webgpu::RenderPassEncoder CreateRenderPassEncoder(const webgpu::CommandEncoder
//   &command_encoder);
//
//   void SetTextureView(const webgpu::Device &device, const webgpu::TextureView &texture_view);
//
// private:
//   void UpdateRenderPassEncoderBuilder();
//
//   webgpu::BindGroupLayout bind_group_layout_;
//   webgpu::RenderPipeline render_pipeline_;
//   webgpu::BindGroup bind_group_;
//   webgpu::RenderPassEncoderBuilder render_pass_encoder_builder_;
//   webgpu::Sampler sampler_;
// };

void Blit(
    const webgpu::TextureView &destination,
    const WGPUTextureFormat destination_format,
    const webgpu::TextureView &source,
    const webgpu::Device &device,
    const webgpu::CommandEncoder &command_encoder);

} // namespace rigel::graphics
