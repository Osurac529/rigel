#pragma once

#include <string_view>

#include <webgpu/wgpu.h>

#include "graphics/fragment_state_builder.hpp"

namespace rigel::graphics {

class ShaderModule;
class RenderPipeline;
class Device;

class RenderPipelineBuilder {
public:
  RenderPipelineBuilder();

  RenderPipelineBuilder &
  SetVertexShader(const ShaderModule &vertex_shader, std::string_view entry_point);

  RenderPipelineBuilder &SetFragmentState(const FragmentState &fragment_state);

  RenderPipelineBuilder &SetTopology(WGPUPrimitiveTopology topology);

  RenderPipelineBuilder &SetCullMode(WGPUCullMode cull_mode);

  RenderPipelineBuilder &SetFrontFace(WGPUFrontFace front_face);

  RenderPipeline Build(Device &device);

private:
  FragmentState fragment_state_;
  WGPURenderPipelineDescriptor descriptor_ = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT;
};

} // namespace rigel::graphics
