#pragma once

#include <string_view>
#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/color_target_state_builder.hpp"

namespace webgpu {

struct FragmentState {
  std::vector<ColorTargetState> targets_;
  WGPUFragmentState state_ = WGPU_FRAGMENT_STATE_INIT;
};

class ShaderModule;

class FragmentStateBuilder {
public:
  FragmentStateBuilder &SetShader(const ShaderModule &shader, std::string_view entry_point);

  FragmentStateBuilder &AddColorTarget(const ColorTargetState &color_target);

  const FragmentState &Build() const;

private:
  FragmentState state_;
};

} // namespace webgpu
