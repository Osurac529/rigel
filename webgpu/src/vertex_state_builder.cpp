#include "webgpu/vertex_state_builder.hpp"

#include "webgpu/shader_module.hpp"

namespace webgpu {

VertexState::VertexState(
    const ShaderModule &shader_module,
    const std::string &entry_point,
    const std::vector<VertexBufferLayout> &buffer_layouts)
    : shader_module_(shader_module), entry_point_(entry_point), buffer_layouts_(buffer_layouts) {}

const WGPUVertexState &VertexState::Get() {
  state_.entryPoint.data = entry_point_.data();
  state_.entryPoint.length = entry_point_.length();
  state_.module = shader_module_.handle();

  wgpu_buffer_layouts_.clear();
  wgpu_buffer_layouts_.reserve(buffer_layouts_.size());

  for (auto &buffer_layout : buffer_layouts_) {
    wgpu_buffer_layouts_.push_back(buffer_layout.Get());
  }

  state_.bufferCount = wgpu_buffer_layouts_.size();
  state_.buffers = wgpu_buffer_layouts_.data();

  return state_;
}

VertexStateBuilder &
VertexStateBuilder::SetShader(const ShaderModule &shader, std::string entry_point) {
  shader_module_ = shader;
  entry_point_ = std::move(entry_point);

  return *this;
}

VertexStateBuilder &
VertexStateBuilder::AddVertexBufferLayout(const VertexBufferLayout &buffer_layout) {
  buffer_layouts_.push_back(buffer_layout);

  return *this;
}

VertexState VertexStateBuilder::Build() const {
  return VertexState(shader_module_, entry_point_, buffer_layouts_);
}

} // namespace webgpu
