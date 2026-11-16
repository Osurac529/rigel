#include "webgpu/vertex_buffer_layout_builder.hpp"

namespace webgpu {

VertexBufferLayoutBuilder::VertexBufferLayoutBuilder() {
  layout_.layout_.stepMode = WGPUVertexStepMode_Vertex;
}

VertexBufferLayoutBuilder &
VertexBufferLayoutBuilder::SetStepMode(const WGPUVertexStepMode step_mode) {
  layout_.layout_.stepMode = step_mode;

  return *this;
}

VertexBufferLayoutBuilder &VertexBufferLayoutBuilder::SetStride(const std::uint64_t stride) {
  layout_.layout_.arrayStride = stride;

  return *this;
}

VertexBufferLayoutBuilder &VertexBufferLayoutBuilder::AddAttribute(
    const WGPUVertexFormat format,
    const std::uint64_t offset,
    const std::uint32_t shader_location) {
  WGPUVertexAttribute vertex_attribute = WGPU_VERTEX_ATTRIBUTE_INIT;
  vertex_attribute.format = format;
  vertex_attribute.offset = offset;
  vertex_attribute.shaderLocation = shader_location;

  layout_.attributes_.push_back(vertex_attribute);

  return *this;
}

const VertexBufferLayout &VertexBufferLayoutBuilder::Build() const {
  return layout_;
}

} // namespace webgpu