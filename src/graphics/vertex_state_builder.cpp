#include "graphics/vertex_state_builder.hpp"

#include "graphics/shader_module.hpp"

namespace rigel::graphics {

VertexStateBuilder &
VertexStateBuilder::SetShader(const ShaderModule &shader, std::string_view entry_point) {
  state_.state_.module = shader.native();
  state_.state_.entryPoint.data = entry_point.data();
  state_.state_.entryPoint.length = entry_point.length();

  return *this;
}

VertexStateBuilder &
VertexStateBuilder::AddVertexBufferLayout(const VertexBufferLayout &buffer_layout) {
  state_.buffer_layouts_.push_back(buffer_layout);

  return *this;
}

VertexState VertexStateBuilder::Build() {
  return state_;
}

} // namespace rigel::graphics
