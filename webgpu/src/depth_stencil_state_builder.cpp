#include "webgpu/depth_stencil_state_builder.hpp"

namespace webgpu {

DepthStencilStateBuilder::DepthStencilStateBuilder() {
  state_.format = WGPUTextureFormat_Depth24Plus;
  state_.depthWriteEnabled = WGPUOptionalBool_True;
  state_.depthCompare = WGPUCompareFunction_Less;
  state_.stencilReadMask = 0;
  state_.stencilWriteMask = 0;
}

DepthStencilStateBuilder &DepthStencilStateBuilder::SetFormat(const WGPUTextureFormat value) {
  state_.format = value;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetDepthWriteEnabled(const WGPUOptionalBool value) {
  state_.depthWriteEnabled = value;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetDepthCompare(const WGPUCompareFunction value) {
  state_.depthCompare = value;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetStencilFront(const WGPUStencilFaceState value) {
  state_.stencilFront = value;

  return *this;
}

DepthStencilStateBuilder &
DepthStencilStateBuilder::SetStencilBack(const WGPUStencilFaceState value) {
  state_.stencilBack = value;

  return *this;
}

DepthStencilStateBuilder &DepthStencilStateBuilder::SetStencilReadMask(const std::uint32_t value) {
  state_.stencilReadMask = value;

  return *this;
}

DepthStencilStateBuilder &DepthStencilStateBuilder::SetStencilWriteMask(const std::uint32_t value) {
  state_.stencilWriteMask = value;

  return *this;
}

DepthStencilStateBuilder &DepthStencilStateBuilder::SetDepthBias(const std::int32_t value) {
  state_.depthBias = value;

  return *this;
}

DepthStencilStateBuilder &DepthStencilStateBuilder::SetDepthBiasSlopeScale(const float value) {
  state_.depthBiasSlopeScale = value;

  return *this;
}

DepthStencilStateBuilder &DepthStencilStateBuilder::SetDepthBiasClamp(const float value) {
  state_.depthBiasClamp = value;

  return *this;
}

const WGPUDepthStencilState &DepthStencilStateBuilder::Build() const {
  return state_;
}

} // namespace webgpu
