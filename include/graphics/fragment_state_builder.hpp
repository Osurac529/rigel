#pragma once

#include <string_view>
#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/color_target_state_builder.hpp"

namespace rigel::graphics {

class FragmentState {
public:
  FragmentState() = default;

  explicit FragmentState(
      const std::vector<ColorTargetState> &targets,
      const WGPUFragmentState &state)
      : targets_(targets), state_(state) {
    Bind();
  }

  FragmentState(const FragmentState &other) : targets_(other.targets_), state_(other.state_) {
    Bind();
  }

  FragmentState &operator=(const FragmentState &other) {
    if (this != &other) {
      targets_ = other.targets_;
      state_ = other.state_;

      Bind();
    }

    return *this;
  }

  FragmentState(FragmentState &&other) noexcept
      : targets_(std::move(other.targets_)), state_(other.state_) {
    Bind();
  }

  FragmentState &operator=(FragmentState &&other) noexcept {
    if (this != &other) {
      targets_ = std::move(other.targets_);
      state_ = other.state_;

      Bind();
    }

    return *this;
  }

  operator const WGPUFragmentState &() const { return state_; }

private:
  void Bind() {
    wgpu_targets_.clear();

    for (const auto &target : targets_) {
      wgpu_targets_.push_back(target);
    }

    state_.targetCount = wgpu_targets_.size();
    state_.targets = wgpu_targets_.data();
  }

  std::vector<ColorTargetState> targets_;
  std::vector<WGPUColorTargetState> wgpu_targets_;
  WGPUFragmentState state_ = WGPU_FRAGMENT_STATE_INIT;
};

class ShaderModule;

class FragmentStateBuilder {
public:
  FragmentStateBuilder &SetShader(const ShaderModule &shader, std::string_view entry_point);

  FragmentStateBuilder &AddColorTarget(const ColorTargetState &color_target);

  FragmentState Build() const;

private:
  std::vector<ColorTargetState> targets_;
  WGPUFragmentState state_ = WGPU_FRAGMENT_STATE_INIT;
};

} // namespace rigel::graphics
