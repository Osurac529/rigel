#pragma once

#include <vector>

#include <webgpu/wgpu.h>

namespace webgpu {

class VertexBufferLayout {
public:
  VertexBufferLayout() = default;

  explicit VertexBufferLayout(
      WGPUVertexBufferLayout layout,
      const std::vector<WGPUVertexAttribute> &attributes);

  const WGPUVertexBufferLayout &Get();

private:
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

  VertexBufferLayout Build() const;

private:
  std::vector<WGPUVertexAttribute> attributes_;
  WGPUVertexBufferLayout layout_ = WGPU_VERTEX_BUFFER_LAYOUT_INIT;
};

} // namespace webgpu
