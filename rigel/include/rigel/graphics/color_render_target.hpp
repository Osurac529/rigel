#pragma once

#include "webgpu/webgpu.hpp"

namespace rigel::graphics {

class ColorRenderTarget {
public:
  ColorRenderTarget() = default;

  explicit ColorRenderTarget(WGPUTextureFormat format);

  explicit ColorRenderTarget(
      const webgpu::Device &device,
      WGPUTextureFormat format,
      std::uint32_t width,
      std::uint32_t height);

  ColorRenderTarget &
  Resize(const webgpu::Device &device, std::uint32_t width, std::uint32_t height);

  ColorRenderTarget &SetColorBlendState(
      WGPUBlendOperation operation,
      WGPUBlendFactor source_factor,
      WGPUBlendFactor destination_factor);

  ColorRenderTarget &SetAlphaBlendState(
      WGPUBlendOperation operation,
      WGPUBlendFactor source_factor,
      WGPUBlendFactor destination_factor);

  ColorRenderTarget &SetColorWriteMask(WGPUColorWriteMask mask);

  ColorRenderTarget &SetFormat(WGPUTextureFormat format);

  ColorRenderTarget &SetView(const webgpu::TextureView &view);

  ColorRenderTarget &SetWeakView(const webgpu::TextureView &view);

  ColorRenderTarget &SetDepthSlice(std::uint32_t depth_slice);

  ColorRenderTarget &SetResolveTarget(const webgpu::TextureView &resolve_target);

  ColorRenderTarget &SetLoadOp(WGPULoadOp load_op);

  ColorRenderTarget &SetStoreOp(WGPUStoreOp store_op);

  ColorRenderTarget &SetClearValue(const WGPUColor &clear_value);

  WGPUTextureFormat GetFormat() const;

  const webgpu::ColorTargetState &state();

  const webgpu::RenderPassColorAttachment &attachment();

private:
  WGPUTextureFormat format_ = WGPUTextureFormat_Undefined;
  webgpu::Texture texture_;
  webgpu::TextureView view_;
  webgpu::ColorTargetStateBuilder state_builder_;
  webgpu::ColorTargetState state_;
  webgpu::RenderPassColorAttachmentBuilder attachment_builder_;
  webgpu::RenderPassColorAttachment attachment_;
  bool is_state_dirty_ = false;
  bool is_attachment_dirty_ = false;
};

} // namespace rigel::graphics
