#pragma once

#include <string_view>
#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/color_target_state_builder.hpp"

namespace rigel::graphics {

struct FragmentState {
  std::vector<ColorTargetState> targets_;
  WGPUFragmentState state_ = WGPU_FRAGMENT_STATE_INIT;
};

class ShaderModule;

class FragmentStateBuilder {
public:
  FragmentStateBuilder &SetShader(const ShaderModule &shader, std::string_view entry_point);

  FragmentStateBuilder &AddColorTarget(const ColorTargetState &color_target);

  FragmentState Build() const;

private:
  FragmentState state_;
};

} // namespace rigel::graphics
