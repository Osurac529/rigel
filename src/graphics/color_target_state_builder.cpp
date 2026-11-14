#include "graphics/color_target_state_builder.hpp"

namespace rigel::graphics {

ColorTargetStateBuilder::ColorTargetStateBuilder() {
  blend_state_.color.srcFactor = WGPUBlendFactor_SrcAlpha;
  blend_state_.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
  blend_state_.color.operation = WGPUBlendOperation_Add;

  blend_state_.alpha.srcFactor = WGPUBlendFactor_Zero;
  blend_state_.alpha.dstFactor = WGPUBlendFactor_One;
  blend_state_.alpha.operation = WGPUBlendOperation_Add;

  state_.blend = &blend_state_;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetColorBlendState(
    WGPUBlendOperation operation,
    WGPUBlendFactor source_factor,
    WGPUBlendFactor destination_factor) {
  blend_state_.color.srcFactor = source_factor;
  blend_state_.color.dstFactor = destination_factor;
  blend_state_.color.operation = operation;

  return *this;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetAlphaBlendState(
    WGPUBlendOperation operation,
    WGPUBlendFactor source_factor,
    WGPUBlendFactor destination_factor) {
  blend_state_.alpha.srcFactor = source_factor;
  blend_state_.alpha.dstFactor = destination_factor;
  blend_state_.alpha.operation = operation;

  return *this;
}

ColorTargetStateBuilder &ColorTargetStateBuilder::SetColorWriteMask(WGPUColorWriteMask mask) {
  state_.writeMask = mask;

  return *this;
}

ColorTargetStateBuilder &
ColorTargetStateBuilder::SetTextureFormat(WGPUTextureFormat texture_format) {
  state_.format = texture_format;

  return *this;
}

ColorTargetState ColorTargetStateBuilder::Build() {
  return ColorTargetState(blend_state_, state_);
}

} // namespace rigel::graphics
