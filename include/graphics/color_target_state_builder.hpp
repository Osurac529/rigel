#pragma once

#include <webgpu/wgpu.h>

namespace rigel::graphics {

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

  //
  // If  WGPUTextureFormat_Undefined,  *indicates a "hole" in the parent @ref WGPUFragmentState
  // `targets` array *the pipeline does not output a value at this `location`.
  //
  ColorTargetStateBuilder &SetTextureFormat(WGPUTextureFormat texture_format);

  ColorTargetState Build();

private:
  ColorTargetState state_;
};

} // namespace rigel::graphics
