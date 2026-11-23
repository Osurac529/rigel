#include "webgpu/depth_stencil_state_builder.hpp"

namespace webgpu {

DepthStencilStateBuilder::DepthStencilStateBuilder() {
  state_.format = WGPUTextureFormat_Depth24Plus;
  state_.depthWriteEnabled = WGPUOptionalBool_True;
  state_.depthCompare = WGPUCompareFunction_Less;
  state_.stencilReadMask = 0;
  state_.stencilWriteMask = 0;
}

DepthStencilStateBuilder &DepthStencilStateBuilder::SetFormat(const WGPUTextureFormat format) {
  is_dirty_ = is_dirty_ || format != state_.format;
  state_.format = format;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetDepthWriteEnabled(const WGPUOptionalBool depth_write_enabled) {
  is_dirty_ = is_dirty_ || depth_write_enabled != state_.depthWriteEnabled;
  state_.depthWriteEnabled = depth_write_enabled;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetDepthCompare(const WGPUCompareFunction depth_compare) {
  is_dirty_ = is_dirty_ || depth_compare != state_.depthCompare;
  state_.depthCompare = depth_compare;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetStencilFront(const WGPUStencilFaceState stencil_front) {
  is_dirty_ = is_dirty_ || stencil_front.compare != state_.stencilFront.compare ||
              stencil_front.depthFailOp != state_.stencilFront.depthFailOp ||
              stencil_front.failOp != state_.stencilFront.failOp ||
              stencil_front.passOp != state_.stencilFront.passOp;
  state_.stencilFront = stencil_front;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetStencilBack(const WGPUStencilFaceState stencil_back) {
  is_dirty_ = stencil_back.compare != state_.stencilFront.compare || is_dirty_ ||
              stencil_back.depthFailOp != state_.stencilFront.depthFailOp ||
              stencil_back.failOp != state_.stencilFront.failOp ||
              stencil_back.passOp != state_.stencilFront.passOp;
  state_.stencilBack = stencil_back;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetStencilReadMask(const std::uint32_t stencil_read_mask) {
  is_dirty_ = is_dirty_ || stencil_read_mask != state_.stencilReadMask;
  state_.stencilReadMask = stencil_read_mask;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetStencilWriteMask(const std::uint32_t stencil_write_mask) {
  is_dirty_ = is_dirty_ || stencil_write_mask != state_.stencilWriteMask;
  state_.stencilWriteMask = stencil_write_mask;

  return *this;
}

DepthStencilStateBuilder &DepthStencilStateBuilder::SetDepthBias(const std::int32_t depth_bias) {
  is_dirty_ = is_dirty_ || depth_bias != state_.depthBias;
  state_.depthBias = depth_bias;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetDepthBiasSlopeScale(const float depth_bias_slope_scale) {
  is_dirty_ = is_dirty_ || depth_bias_slope_scale != state_.depthBiasSlopeScale;
  state_.depthBiasSlopeScale = depth_bias_slope_scale;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetDepthBiasClamp(const float depth_bias_clamp) {
  is_dirty_ = is_dirty_ || depth_bias_clamp != state_.depthBiasClamp;
  state_.depthBiasClamp = depth_bias_clamp;

  return *this;
}

const WGPUDepthStencilState &DepthStencilStateBuilder::Build() const {
  is_dirty_ = false;

  return state_;
}

bool DepthStencilStateBuilder::IsDirty() const {
  return is_dirty_;
}

} // namespace webgpu
