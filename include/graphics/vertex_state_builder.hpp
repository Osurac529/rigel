#pragma once

#include <string_view>
#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/vertex_buffer_layout_builder.hpp"

namespace rigel::graphics {

class ShaderModule;

struct VertexState {
  std::vector<VertexBufferLayout> buffer_layouts_;
  WGPUVertexState state_;
};

class VertexStateBuilder {
public:
  VertexStateBuilder &SetShader(const ShaderModule &shader, std::string_view entry_point);

  VertexStateBuilder &AddVertexBufferLayout(const VertexBufferLayout &buffer_layout);

  VertexState Build();

private:
  VertexState state_;
};

} // namespace rigel::graphics
