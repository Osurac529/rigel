#include "webgpu/color_target_state_builder.hpp"

namespace webgpu {

ColorTargetState::ColorTargetState(
    const WGPUBlendState &blend_state,
    const WGPUColorTargetState &state,
    const bool is_blend_set)
    : blend_state_(blend_state), state_(state), is_blend_set_(is_blend_set) {}

const WGPUColorTargetState &ColorTargetState::Get() {
  if (is_blend_set_) {
    state_.blend = &blend_state_;
  }

  return state_;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetColorBlendState(
    const WGPUBlendOperation operation,
    const WGPUBlendFactor source_factor,
    const WGPUBlendFactor destination_factor) {
  is_blend_set_ = true;
  is_dirty_ = is_dirty_ || blend_state_.color.srcFactor != source_factor ||
              blend_state_.color.dstFactor != destination_factor ||
              blend_state_.color.operation != operation;
  blend_state_.color.srcFactor = source_factor;
  blend_state_.color.dstFactor = destination_factor;
  blend_state_.color.operation = operation;

  return *this;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetAlphaBlendState(
    const WGPUBlendOperation operation,
    const WGPUBlendFactor source_factor,
    const WGPUBlendFactor destination_factor) {
  is_blend_set_ = true;
  is_dirty_ = is_dirty_ || blend_state_.alpha.srcFactor != source_factor ||
              blend_state_.alpha.dstFactor != destination_factor ||
              blend_state_.alpha.operation != operation;
  blend_state_.alpha.srcFactor = source_factor;
  blend_state_.alpha.dstFactor = destination_factor;
  blend_state_.alpha.operation = operation;

  return *this;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetColorWriteMask(const WGPUColorWriteMask mask) {
  is_dirty_ = is_dirty_ || state_.writeMask != mask;
  state_.writeMask = mask;

  return *this;
}

ColorTargetStateBuilder &
ColorTargetStateBuilder::SetTextureFormat(const WGPUTextureFormat texture_format) {
  is_dirty_ = is_dirty_ || state_.format != texture_format;
  state_.format = texture_format;

  return *this;
}

ColorTargetState ColorTargetStateBuilder::Build() const {
  is_dirty_ = false;

  return ColorTargetState(blend_state_, state_, is_blend_set_);
}

bool ColorTargetStateBuilder::IsDirty() const {
  return is_dirty_;
}

} // namespace webgpu
