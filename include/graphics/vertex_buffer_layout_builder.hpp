#pragma once

#include <vector>

#include <webgpu/wgpu.h>

namespace rigel::graphics {

struct VertexBufferLayout {
  std::vector<WGPUVertexAttribute> attributes_;
  WGPUVertexBufferLayout layout_ = WGPU_VERTEX_BUFFER_LAYOUT_INIT;
};

class VertexBufferLayoutBuilder {
public:
  VertexBufferLayoutBuilder();

  VertexBufferLayoutBuilder &SetStepMode(WGPUVertexStepMode step_mode);

  VertexBufferLayoutBuilder &SetStride(std::uint64_t stride);

  VertexBufferLayoutBuilder &
  AddAttribute(WGPUVertexFormat format, std::uint64_t offset, std::uint32_t shader_location);

  VertexBufferLayout Build();

private:
  VertexBufferLayout layout_;
};

} // namespace rigel::graphics
