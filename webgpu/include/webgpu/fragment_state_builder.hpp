#pragma once

#include <string>
#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/color_target_state_builder.hpp"
#include "webgpu/shader_module.hpp"

namespace webgpu {

class FragmentState {
public:
  FragmentState() = default;

  explicit FragmentState(
      const ShaderModule &shader_module,
      const std::string &entry_point,
      const std::vector<ColorTargetState> &targets,
      const WGPUFragmentState &state);

  const WGPUFragmentState &Get();

private:
  ShaderModule shader_module_;
  std::string entry_point_;
  std::vector<ColorTargetState> targets_;
  std::vector<WGPUColorTargetState> wgpu_targets_;
  WGPUFragmentState state_ = WGPU_FRAGMENT_STATE_INIT;
};

class FragmentStateBuilder {
public:
  FragmentStateBuilder &AddColorTarget(const ColorTargetState &color_target);

  FragmentStateBuilder &SetShader(const ShaderModule &shader, std::string entry_point);

  FragmentState Build() const;

private:
  ShaderModule shader_module_;
  std::string entry_point_;
  std::vector<ColorTargetState> targets_;
  std::vector<WGPUColorTargetState> wgpu_targets_;
  WGPUFragmentState state_ = WGPU_FRAGMENT_STATE_INIT;
};

} // namespace webgpu
