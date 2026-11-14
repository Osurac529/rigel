#pragma once

#include <algorithm>

#include <webgpu/wgpu.h>

namespace rigel::graphics {

class ColorTargetState {
public:
  explicit ColorTargetState(const WGPUBlendState &blend_state, const WGPUColorTargetState &state)
      : blend_state_(blend_state), state_(state) {
    Bind();
  }

  ColorTargetState(const ColorTargetState &other)
      : blend_state_(other.blend_state_), state_(other.state_) {
    Bind();
  }

  ColorTargetState &operator=(const ColorTargetState &other) {
    if (this != &other) {
      blend_state_ = other.blend_state_;
      state_ = other.state_;

      Bind();
    }

    return *this;
  }

  ColorTargetState(ColorTargetState &&other) noexcept
      : blend_state_(other.blend_state_), state_(other.state_) {
    Bind();
  }

  ColorTargetState &operator=(ColorTargetState &&other) noexcept {
    if (this != &other) {
      blend_state_ = other.blend_state_;
      state_ = other.state_;

      Bind();
    }

    return *this;
  }

  operator const WGPUColorTargetState &() const { return state_; }

private:
  void Bind() { state_.blend = &blend_state_; }

  WGPUBlendState blend_state_;
  WGPUColorTargetState state_;
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
  WGPUBlendState blend_state_ = WGPU_BLEND_STATE_INIT;
  WGPUColorTargetState state_ = WGPU_COLOR_TARGET_STATE_INIT;
};

} // namespace rigel::graphics
