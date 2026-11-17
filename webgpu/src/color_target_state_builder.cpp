#include "webgpu/color_target_state_builder.hpp"

namespace webgpu {

ColorTargetState::ColorTargetState(
    const WGPUBlendState &blend_state,
    const WGPUColorTargetState &state)
    : blend_state_(blend_state), state_(state) {}

const WGPUColorTargetState &ColorTargetState::Get() {
  state_.blend = &blend_state_;
  return state_;
}

ColorTargetStateBuilder::ColorTargetStateBuilder() {
  blend_state_.color.srcFactor = WGPUBlendFactor_SrcAlpha;
  blend_state_.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
  blend_state_.color.operation = WGPUBlendOperation_Add;

  blend_state_.alpha.srcFactor = WGPUBlendFactor_Zero;
  blend_state_.alpha.dstFactor = WGPUBlendFactor_One;
  blend_state_.alpha.operation = WGPUBlendOperation_Add;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetColorBlendState(
    const WGPUBlendOperation operation,
    const WGPUBlendFactor source_factor,
    const WGPUBlendFactor destination_factor) {
  blend_state_.color.srcFactor = source_factor;
  blend_state_.color.dstFactor = destination_factor;
  blend_state_.color.operation = operation;

  return *this;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetAlphaBlendState(
    const WGPUBlendOperation operation,
    const WGPUBlendFactor source_factor,
    const WGPUBlendFactor destination_factor) {
  blend_state_.alpha.srcFactor = source_factor;
  blend_state_.alpha.dstFactor = destination_factor;
  blend_state_.alpha.operation = operation;

  return *this;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetColorWriteMask(const WGPUColorWriteMask mask) {
  state_.writeMask = mask;

  return *this;
}

ColorTargetStateBuilder &
ColorTargetStateBuilder::SetTextureFormat(const WGPUTextureFormat texture_format) {
  state_.format = texture_format;

  return *this;
}

ColorTargetState ColorTargetStateBuilder::Build() const {
  return ColorTargetState(blend_state_, state_);
}

} // namespace webgpu
