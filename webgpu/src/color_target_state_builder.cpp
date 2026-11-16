#include "webgpu/color_target_state_builder.hpp"

namespace webgpu {

ColorTargetStateBuilder::ColorTargetStateBuilder() {
  state_.blend_state_.color.srcFactor = WGPUBlendFactor_SrcAlpha;
  state_.blend_state_.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
  state_.blend_state_.color.operation = WGPUBlendOperation_Add;

  state_.blend_state_.alpha.srcFactor = WGPUBlendFactor_Zero;
  state_.blend_state_.alpha.dstFactor = WGPUBlendFactor_One;
  state_.blend_state_.alpha.operation = WGPUBlendOperation_Add;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetColorBlendState(
    const WGPUBlendOperation operation,
    const WGPUBlendFactor source_factor,
    const WGPUBlendFactor destination_factor) {
  state_.blend_state_.color.srcFactor = source_factor;
  state_.blend_state_.color.dstFactor = destination_factor;
  state_.blend_state_.color.operation = operation;

  return *this;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetAlphaBlendState(
    const WGPUBlendOperation operation,
    const WGPUBlendFactor source_factor,
    const WGPUBlendFactor destination_factor) {
  state_.blend_state_.alpha.srcFactor = source_factor;
  state_.blend_state_.alpha.dstFactor = destination_factor;
  state_.blend_state_.alpha.operation = operation;

  return *this;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetColorWriteMask(const WGPUColorWriteMask mask) {
  state_.state_.writeMask = mask;

  return *this;
}

ColorTargetStateBuilder &
ColorTargetStateBuilder::SetTextureFormat(const WGPUTextureFormat texture_format) {
  state_.state_.format = texture_format;

  return *this;
}

const ColorTargetState &ColorTargetStateBuilder::Build() const {
  return state_;
}

} // namespace webgpu
