#pragma once

#include <string>
#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/shader_module.hpp"
#include "webgpu/vertex_buffer_layout_builder.hpp"

namespace webgpu {

class VertexState {
public:
  VertexState() = default;

  explicit VertexState(
      const ShaderModule &shader_module,
      const std::string &entry_point,
      const std::vector<VertexBufferLayout> &buffer_layouts);

  const WGPUVertexState &Get();

private:
  ShaderModule shader_module_;
  std::string entry_point_;
  std::vector<VertexBufferLayout> buffer_layouts_;
  std::vector<WGPUVertexBufferLayout> wgpu_buffer_layouts_;
  WGPUVertexState state_ = WGPU_VERTEX_STATE_INIT;
};

class VertexStateBuilder {
public:
  VertexStateBuilder &SetShader(const ShaderModule &shader, std::string entry_point);

  VertexStateBuilder &AddVertexBufferLayout(const VertexBufferLayout &buffer_layout);

  VertexState Build() const;

private:
  ShaderModule shader_module_;
  std::string entry_point_;
  std::vector<VertexBufferLayout> buffer_layouts_;
};

} // namespace webgpu
