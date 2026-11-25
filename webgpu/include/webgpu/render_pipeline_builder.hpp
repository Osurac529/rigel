#pragma once

#include <string_view>

#include <webgpu/wgpu.h>

#include "webgpu/depth_stencil_state_builder.hpp"
#include "webgpu/fragment_state_builder.hpp"
#include "webgpu/pipeline_layout.hpp"
#include "webgpu/vertex_state_builder.hpp"

namespace webgpu {

class ShaderModule;
class RenderPipeline;
class Device;

class RenderPipelineBuilder {
public:
  RenderPipelineBuilder();

  RenderPipelineBuilder &SetDepthStencilState(const WGPUDepthStencilState &state);

  RenderPipelineBuilder &SetVertexState(const VertexState &vertex_state);

  RenderPipelineBuilder &SetFragmentState(const FragmentState &fragment_state);

  RenderPipelineBuilder &SetTopology(WGPUPrimitiveTopology topology);

  RenderPipelineBuilder &SetCullMode(WGPUCullMode cull_mode);

  RenderPipelineBuilder &SetFrontFace(WGPUFrontFace front_face);

  RenderPipelineBuilder &SetLayout(const PipelineLayout &layout);

  RenderPipeline Build(const Device &device);

private:
  bool depth_stencil_state_set_ = false;
  bool fragment_state_set_ = false;
  WGPUDepthStencilState depth_stencil_state_ = WGPU_DEPTH_STENCIL_STATE_INIT;
  PipelineLayout layout_;
  FragmentState fragment_state_;
  VertexState vertex_state_;
  WGPURenderPipelineDescriptor descriptor_ = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT;
};

} // namespace webgpu
