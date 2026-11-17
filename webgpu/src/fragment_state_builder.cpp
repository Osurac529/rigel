#include "webgpu/fragment_state_builder.hpp"

namespace webgpu {

FragmentState::FragmentState(
    const ShaderModule &shader_module,
    const std::string &entry_point,
    const std::vector<ColorTargetState> &targets,
    const WGPUFragmentState &state)
    : shader_module_(shader_module), entry_point_(entry_point), targets_(targets), state_(state) {}

const WGPUFragmentState &FragmentState::Get() {
  state_.entryPoint.data = entry_point_.data();
  state_.entryPoint.length = entry_point_.length();
  state_.module = shader_module_.handle();

  wgpu_targets_.clear();
  wgpu_targets_.reserve(targets_.size());

  for (auto &target : targets_) {
    wgpu_targets_.emplace_back(target.Get());
  }

  state_.targetCount = wgpu_targets_.size();
  state_.targets = wgpu_targets_.data();

  return state_;
}

FragmentStateBuilder &
FragmentStateBuilder::SetShader(const ShaderModule &shader, std::string entry_point) {
  shader_module_ = shader;
  entry_point_ = std::move(entry_point);

  return *this;
}

FragmentStateBuilder &FragmentStateBuilder::AddColorTarget(const ColorTargetState &color_target) {
  targets_.emplace_back(color_target);

  return *this;
}

FragmentState FragmentStateBuilder::Build() const {
  return FragmentState(shader_module_, entry_point_, targets_, state_);
}

} // namespace webgpu
