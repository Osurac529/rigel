#pragma once

#include <webgpu/wgpu.h>

namespace webgpu {

class ColorTargetState {
public:
  ColorTargetState() = default;

  explicit ColorTargetState(const WGPUBlendState &blend_state, const WGPUColorTargetState &state);

  const WGPUColorTargetState &Get();

private:
  WGPUBlendState blend_state_ = WGPU_BLEND_STATE_INIT;
  WGPUColorTargetState state_ = WGPU_COLOR_TARGET_STATE_INIT;
};

class ColorTargetStateBuilder {
public:
  ColorTargetStateBuilder();

  ColorTargetStateBuilder &SetColorBlendState(
      WGPUBlendOperation operation,
      WGPUBlendFactor source_factor,
      WGPUBlendFactor destination_factor);

  ColorTargetStateBuilder &SetAlphaBlendState(
      WGPUBlendOperation operation,
      WGPUBlendFactor source_factor,
      WGPUBlendFactor destination_factor);

  ColorTargetStateBuilder &SetColorWriteMask(WGPUColorWriteMask mask);

  ColorTargetStateBuilder &SetTextureFormat(WGPUTextureFormat texture_format);

  ColorTargetState Build() const;

  bool IsDirty() const;

private:
  WGPUBlendState blend_state_ = WGPU_BLEND_STATE_INIT;
  WGPUColorTargetState state_ = WGPU_COLOR_TARGET_STATE_INIT;
  mutable bool is_dirty_ = true;
};

} // namespace webgpu
