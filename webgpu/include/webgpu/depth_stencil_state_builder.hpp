#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

namespace webgpu {

class DepthStencilStateBuilder {
public:
  DepthStencilStateBuilder();

  DepthStencilStateBuilder &SetFormat(WGPUTextureFormat value);

  DepthStencilStateBuilder &SetDepthWriteEnabled(WGPUOptionalBool value);

  DepthStencilStateBuilder &SetDepthCompare(WGPUCompareFunction value);

  DepthStencilStateBuilder &SetStencilFront(WGPUStencilFaceState value);

  DepthStencilStateBuilder &SetStencilBack(WGPUStencilFaceState value);

  DepthStencilStateBuilder &SetStencilReadMask(std::uint32_t value);

  DepthStencilStateBuilder &SetStencilWriteMask(std::uint32_t value);

  DepthStencilStateBuilder &SetDepthBias(std::int32_t value);

  DepthStencilStateBuilder &SetDepthBiasSlopeScale(float value);

  DepthStencilStateBuilder &SetDepthBiasClamp(float value);

  const WGPUDepthStencilState &Build() const;

private:
  WGPUDepthStencilState state_ = WGPU_DEPTH_STENCIL_STATE_INIT;
};

} // namespace webgpu
