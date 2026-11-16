#pragma once

#include <string_view>
#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/vertex_buffer_layout_builder.hpp"

namespace webgpu {

class ShaderModule;

struct VertexState {
  std::vector<VertexBufferLayout> buffer_layouts_;
  WGPUVertexState state_;
};

class VertexStateBuilder {
public:
  VertexStateBuilder &SetShader(const ShaderModule &shader, std::string_view entry_point);

  VertexStateBuilder &AddVertexBufferLayout(const VertexBufferLayout &buffer_layout);

  const VertexState &Build() const;

private:
  VertexState state_;
};

} // namespace webgpu
