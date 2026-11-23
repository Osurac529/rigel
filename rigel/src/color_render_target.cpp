#include "rigel/graphics/color_render_target.hpp"

namespace rigel::graphics {

ColorRenderTarget::ColorRenderTarget(const WGPUTextureFormat format) {
  SetFormat(format);
}

ColorRenderTarget::ColorRenderTarget(
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
  SetView(webgpu::TextureViewBuilder().Build(texture_));
}

ColorRenderTarget &ColorRenderTarget::Resize(
    const webgpu::Device &device,
    const std::uint32_t width,
    const std::uint32_t height) {
  texture_ = webgpu::TextureBuilder()
                 .AddViewFormat(texture_.GetFormat())
                 .SetSize({width, height, 1})
                 .SetUsage(WGPUTextureUsage_RenderAttachment)
                 .SetFormat(texture_.GetFormat())
                 .Build(device);

  SetView(webgpu::TextureViewBuilder().Build(texture_));

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetColorBlendState(
    const WGPUBlendOperation operation,
    const WGPUBlendFactor source_factor,
    const WGPUBlendFactor destination_factor) {
  state_builder_.SetColorBlendState(operation, source_factor, destination_factor);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetAlphaBlendState(
    const WGPUBlendOperation operation,
    const WGPUBlendFactor source_factor,
    const WGPUBlendFactor destination_factor) {
  state_builder_.SetAlphaBlendState(operation, source_factor, destination_factor);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetColorWriteMask(const WGPUColorWriteMask mask) {
  state_builder_.SetColorWriteMask(mask);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetFormat(const WGPUTextureFormat format) {
  format_ = format;
  state_builder_.SetTextureFormat(format);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetView(const webgpu::TextureView &view) {
  attachment_builder_.SetView(view);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetWeakView(const webgpu::TextureView &view) {
  attachment_builder_.SetView(view.handle());

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetDepthSlice(const std::uint32_t depth_slice) {
  attachment_builder_.SetDepthSlice(depth_slice);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetResolveTarget(const webgpu::TextureView &resolve_target) {
  attachment_builder_.SetResolveTarget(resolve_target);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetLoadOp(const WGPULoadOp load_op) {
  attachment_builder_.SetLoadOp(load_op);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetStoreOp(const WGPUStoreOp store_op) {
  attachment_builder_.SetStoreOp(store_op);

  return *this;
}

ColorRenderTarget &ColorRenderTarget::SetClearValue(const WGPUColor &clear_value) {
  attachment_builder_.SetClearValue(clear_value);

  return *this;
}

WGPUTextureFormat ColorRenderTarget::GetFormat() const {
  // we wont always have a texture_, so get the format from the member
  return format_;
}

const webgpu::ColorTargetState &ColorRenderTarget::state() {
  if (state_builder_.IsDirty()) {
    state_ = state_builder_.Build();
  }

  return state_;
}

const webgpu::RenderPassColorAttachment &ColorRenderTarget::attachment() {
  if (attachment_builder_.IsDirty()) {
    attachment_ = attachment_builder_.Build();
  }

  return attachment_;
}

} // namespace rigel::graphics
