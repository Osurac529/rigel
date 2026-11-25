#include "rigel/graphics/render_targets.hpp"

namespace rigel::graphics {

void RenderTargets::AddColorTarget(const ColorRenderTarget &color_target) {
  color_targets_.push_back(color_target);
}

void RenderTargets::SetColorTarget(
    const std::uint32_t index,
    const ColorRenderTarget &color_target) {
  if (index >= color_targets_.size()) {
    color_targets_.resize(index + 1);
  }

  color_targets_[index] = color_target;
}

ColorRenderTarget &RenderTargets::GetColorTarget(const std::uint32_t index) {
  return color_targets_[index];
}

void RenderTargets::SetDepthStencilTarget(const DepthStencilRenderTarget &depth_stencil_target) {
  depth_stencil_target_ = depth_stencil_target;
}

DepthStencilRenderTarget &RenderTargets::GetDepthStencilTarget() {
  return depth_stencil_target_;
}

void RenderTargets::Resize(
    const webgpu::Device &device,
    const std::uint32_t width,
    const std::uint32_t height) {
  for (auto &color_target : color_targets_) {
    color_target.Resize(device, width, height);
  }

  depth_stencil_target_.Resize(device, width, height);
}

const std::vector<ColorRenderTarget> &RenderTargets::color_targets() const {
  return color_targets_;
}

std::vector<ColorRenderTarget> &RenderTargets::color_targets() {
  return color_targets_;
}

} // namespace rigel::graphics
