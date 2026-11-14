#include "graphics/fragment_state_builder.hpp"

#include "graphics/color_target_state_builder.hpp"
#include "graphics/graphics_exception.hpp"
#include "graphics/shader_module.hpp"

namespace rigel::graphics {

FragmentStateBuilder &
FragmentStateBuilder::SetShader(const ShaderModule &shader, std::string_view entry_point) {
  state_.module = shader.native();
  state_.entryPoint.data = entry_point.data();
  state_.entryPoint.length = entry_point.length();

  return *this;
}

FragmentStateBuilder &FragmentStateBuilder::AddColorTarget(const ColorTargetState &color_target) {
  targets_.emplace_back(color_target);

  return *this;
}

FragmentState FragmentStateBuilder::Build() const {
  return FragmentState(targets_, state_);
}

} // namespace rigel::graphics
