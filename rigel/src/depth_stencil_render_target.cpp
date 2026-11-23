#include "rigel/graphics/depth_stencil_render_target.hpp"

namespace rigel::graphics {

DepthStencilRenderTarget::DepthStencilRenderTarget(
    const webgpu::Device &device,
    const WGPUTextureFormat format,
    const std::uint32_t width,
    const std::uint32_t height)
    : texture_(
          webgpu::TextureBuilder()
              .AddViewFormat(format)
              .SetSize({width, height, 1})
              .SetUsage(WGPUTextureUsage_RenderAttachment)
              .SetFormat(format)
              .Build(device)) {
  SetFormat(format);
  SetView(webgpu::TextureViewBuilder().SetAspect(WGPUTextureAspect_DepthOnly).Build(texture_));
}

DepthStencilRenderTarget &DepthStencilRenderTarget::Resize(
    const webgpu::Device &device,
    const std::uint32_t width,
    const std::uint32_t height) {
  texture_ = webgpu::TextureBuilder()
                 .AddViewFormat(texture_.GetFormat())
                 .SetSize({width, height, 1})
                 .SetUsage(WGPUTextureUsage_RenderAttachment)
                 .SetFormat(texture_.GetFormat())
                 .Build(device);

  SetView(webgpu::TextureViewBuilder().SetAspect(WGPUTextureAspect_DepthOnly).Build(texture_));

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetFormat(const WGPUTextureFormat format) {
  state_builder_.SetFormat(format);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetDepthWriteEnabled(const WGPUOptionalBool depth_write_enabled) {
  state_builder_.SetDepthWriteEnabled(depth_write_enabled);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetDepthCompare(const WGPUCompareFunction depth_compare) {
  state_builder_.SetDepthCompare(depth_compare);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetStencilFront(const WGPUStencilFaceState stencil_front) {
  state_builder_.SetStencilFront(stencil_front);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetStencilBack(const WGPUStencilFaceState stencil_back) {
  state_builder_.SetStencilBack(stencil_back);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetStencilReadMask(const std::uint32_t stencil_read_mask) {
  state_builder_.SetStencilReadMask(stencil_read_mask);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetStencilWriteMask(const std::uint32_t stencil_write_mask) {
  state_builder_.SetStencilWriteMask(stencil_write_mask);

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetDepthBias(const std::int32_t depth_bias) {
  state_builder_.SetDepthBias(depth_bias);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetDepthBiasSlopeScale(const float depth_bias_slope_scale) {
  state_builder_.SetDepthBiasSlopeScale(depth_bias_slope_scale);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetDepthBiasClamp(const float depth_bias_clamp) {
  state_builder_.SetDepthBiasClamp(depth_bias_clamp);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetView(const webgpu::TextureView &texture_view) {
  attachment_builder_.SetView(texture_view);

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetDepthLoadOp(const WGPULoadOp load_op) {
  attachment_builder_.SetDepthLoadOp(load_op);

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetDepthStoreOp(const WGPUStoreOp store_op) {
  attachment_builder_.SetDepthStoreOp(store_op);

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetDepthClearValue(const float clear_value) {
  attachment_builder_.SetDepthClearValue(clear_value);

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetDepthReadOnly(const WGPUBool read_only) {
  attachment_builder_.SetDepthReadOnly(read_only);

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetStencilLoadOp(const WGPULoadOp load_op) {
  attachment_builder_.SetStencilLoadOp(load_op);

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetStencilStoreOp(const WGPUStoreOp store_op) {
  attachment_builder_.SetStencilStoreOp(store_op);

  return *this;
}

DepthStencilRenderTarget &
DepthStencilRenderTarget::SetStencilClearValue(const std::uint32_t clear_value) {
  attachment_builder_.SetStencilClearValue(clear_value);

  return *this;
}

DepthStencilRenderTarget &DepthStencilRenderTarget::SetStencilReadOnly(const WGPUBool read_only) {
  attachment_builder_.SetStencilReadOnly(read_only);

  return *this;
}

const WGPUDepthStencilState &DepthStencilRenderTarget::state() {
  if (state_builder_.IsDirty()) {
    state_ = state_builder_.Build();
  }

  return state_;
}

const webgpu::RenderPassDepthStencilAttachment &DepthStencilRenderTarget::attachment() {
  if (attachment_builder_.IsDirty()) {
    attachment_ = attachment_builder_.Build();
  }

  return attachment_;
}

} // namespace rigel::graphics
