#pragma once

#include "webgpu/webgpu.hpp"

namespace rigel::graphics {

class DepthStencilRenderTarget {
public:
  DepthStencilRenderTarget() = default;

  explicit DepthStencilRenderTarget(
      const webgpu::Device &device,
      WGPUTextureFormat format,
      std::uint32_t width,
      std::uint32_t height);

  DepthStencilRenderTarget &
  Resize(const webgpu::Device &device, std::uint32_t width, std::uint32_t height);

  DepthStencilRenderTarget &SetFormat(WGPUTextureFormat format);

  DepthStencilRenderTarget &SetDepthWriteEnabled(WGPUOptionalBool depth_write_enabled);

  DepthStencilRenderTarget &SetDepthCompare(WGPUCompareFunction depth_compare);

  DepthStencilRenderTarget &SetStencilFront(WGPUStencilFaceState stencil_front);

  DepthStencilRenderTarget &SetStencilBack(WGPUStencilFaceState stencil_back);

  DepthStencilRenderTarget &SetStencilReadMask(std::uint32_t stencil_read_mask);

  DepthStencilRenderTarget &SetStencilWriteMask(std::uint32_t stencil_write_mask);

  DepthStencilRenderTarget &SetDepthBias(std::int32_t depth_bias);

  DepthStencilRenderTarget &SetDepthBiasSlopeScale(float depth_bias_slope_scale);

  DepthStencilRenderTarget &SetDepthBiasClamp(float depth_bias_clamp);

  DepthStencilRenderTarget &SetView(const webgpu::TextureView &texture_view);

  DepthStencilRenderTarget &SetDepthLoadOp(WGPULoadOp load_op);

  DepthStencilRenderTarget &SetDepthStoreOp(WGPUStoreOp store_op);

  DepthStencilRenderTarget &SetDepthClearValue(float clear_value);

  DepthStencilRenderTarget &SetDepthReadOnly(WGPUBool read_only);

  DepthStencilRenderTarget &SetStencilLoadOp(WGPULoadOp load_op);

  DepthStencilRenderTarget &SetStencilStoreOp(WGPUStoreOp store_op);

  DepthStencilRenderTarget &SetStencilClearValue(std::uint32_t clear_value);

  DepthStencilRenderTarget &SetStencilReadOnly(WGPUBool read_only);

  const WGPUDepthStencilState &state();

  const webgpu::RenderPassDepthStencilAttachment &attachment();

private:
  webgpu::Texture texture_;
  webgpu::TextureView view_;
  webgpu::DepthStencilStateBuilder state_builder_;
  WGPUDepthStencilState state_ = WGPU_DEPTH_STENCIL_STATE_INIT;
  webgpu::RenderPassDepthStencilAttachmentBuilder attachment_builder_;
  webgpu::RenderPassDepthStencilAttachment attachment_;
};

} // namespace rigel::graphics
