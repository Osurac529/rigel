#pragma once

#include <webgpu/wgpu.h>

namespace webgpu {

struct ColorTargetState {
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

  const ColorTargetState &Build() const;

private:
  ColorTargetState state_;
};

} // namespace webgpu
