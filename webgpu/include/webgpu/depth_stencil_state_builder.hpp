#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

namespace webgpu {

class DepthStencilStateBuilder {
public:
  DepthStencilStateBuilder();

  DepthStencilStateBuilder &SetFormat(WGPUTextureFormat format);

  DepthStencilStateBuilder &SetDepthWriteEnabled(WGPUOptionalBool depth_write_enabled);

  DepthStencilStateBuilder &SetDepthCompare(WGPUCompareFunction depth_compare);

  DepthStencilStateBuilder &SetStencilFront(WGPUStencilFaceState stencil_front);

  DepthStencilStateBuilder &SetStencilBack(WGPUStencilFaceState stencil_back);

  DepthStencilStateBuilder &SetStencilReadMask(std::uint32_t stencil_read_mask);

  DepthStencilStateBuilder &SetStencilWriteMask(std::uint32_t stencil_write_mask);

  DepthStencilStateBuilder &SetDepthBias(std::int32_t depth_bias);

  DepthStencilStateBuilder &SetDepthBiasSlopeScale(float depth_bias_slope_scale);

  DepthStencilStateBuilder &SetDepthBiasClamp(float depth_bias_clamp);

  const WGPUDepthStencilState &Build() const;

  bool IsDirty() const;

private:
  WGPUDepthStencilState state_ = WGPU_DEPTH_STENCIL_STATE_INIT;
  mutable bool is_dirty_ = true;
};

} // namespace webgpu
