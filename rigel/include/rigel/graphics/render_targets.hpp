#pragma once

#include "webgpu/webgpu.hpp"

#include "rigel/graphics/color_render_target.hpp"
#include "rigel/graphics/depth_stencil_render_target.hpp"

namespace rigel::graphics {

class RenderTargets {
public:
  void AddColorTarget(const ColorRenderTarget &color_target);

  void SetColorTarget(std::uint32_t index, const ColorRenderTarget &color_target);

  ColorRenderTarget &GetColorTarget(std::uint32_t index);

  void SetDepthStencilTarget(const DepthStencilRenderTarget &depth_stencil_target);

  DepthStencilRenderTarget &GetDepthStencilTarget();

private:
  std::vector<ColorRenderTarget> color_targets_;
  DepthStencilRenderTarget depth_stencil_target_;
};

} // namespace rigel::graphics
