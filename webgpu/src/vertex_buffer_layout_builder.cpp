#include "webgpu/vertex_buffer_layout_builder.hpp"

namespace webgpu {

VertexBufferLayout::VertexBufferLayout(
    WGPUVertexBufferLayout layout,
    const std::vector<WGPUVertexAttribute> &attributes)
    : layout_(layout), attributes_(attributes) {}

const WGPUVertexBufferLayout &VertexBufferLayout::Get() {
  layout_.attributeCount = attributes_.size();
  layout_.attributes = attributes_.data();

  return layout_;
}

VertexBufferLayoutBuilder::VertexBufferLayoutBuilder() {
  layout_.stepMode = WGPUVertexStepMode_Vertex;
}

VertexBufferLayoutBuilder &VertexBufferLayoutBuilder::AddAttribute(
    const WGPUVertexFormat format,
    const std::uint64_t offset,
    const std::uint32_t shader_location) {
  WGPUVertexAttribute vertex_attribute = WGPU_VERTEX_ATTRIBUTE_INIT;
  vertex_attribute.format = format;
  vertex_attribute.offset = offset;
  vertex_attribute.shaderLocation = shader_location;

  attributes_.push_back(vertex_attribute);

  return *this;
}

VertexBufferLayoutBuilder &
VertexBufferLayoutBuilder::SetStepMode(const WGPUVertexStepMode step_mode) {
  layout_.stepMode = step_mode;

  return *this;
}

VertexBufferLayoutBuilder &VertexBufferLayoutBuilder::SetStride(const std::uint64_t stride) {
  layout_.arrayStride = stride;

  return *this;
}

VertexBufferLayout VertexBufferLayoutBuilder::Build() const {
  return VertexBufferLayout(layout_, attributes_);
}

} // namespace webgpu