#include "webgpu/render_pipeline_builder.hpp"

#include "webgpu/device.hpp"
#include "webgpu/fragment_state_builder.hpp"
#include "webgpu/pipeline_layout.hpp"
#include "webgpu/render_pipeline.hpp"
#include "webgpu/shader_module.hpp"

namespace webgpu {

RenderPipelineBuilder::RenderPipelineBuilder() {
  descriptor_.primitive.cullMode = WGPUCullMode_None;
  descriptor_.primitive.frontFace = WGPUFrontFace_CCW;
  descriptor_.primitive.topology = WGPUPrimitiveTopology_TriangleList;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetVertexState(const VertexState &vertex_state) {
  vertex_state_ = vertex_state;

  return *this;
}

RenderPipelineBuilder &
RenderPipelineBuilder::SetFragmentState(const FragmentState &fragment_state) {
  fragment_state_set_ = true;
  fragment_state_ = fragment_state;

  return *this;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetTopology(const WGPUPrimitiveTopology topology) {
  descriptor_.primitive.topology = topology;
  return *this;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetCullMode(const WGPUCullMode cull_mode) {
  descriptor_.primitive.cullMode = cull_mode;

  return *this;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetFrontFace(const WGPUFrontFace front_face) {
  descriptor_.primitive.frontFace = front_face;

  return *this;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetLayout(const PipelineLayout &layout) {
  layout_ = layout;

  return *this;
}

RenderPipeline RenderPipelineBuilder::Build(Device &device) {
  if (fragment_state_set_) {
    descriptor_.fragment = &fragment_state_.Get();
  }

  descriptor_.vertex = vertex_state_.Get();
  descriptor_.layout = layout_.handle();

  return RenderPipeline(wgpuDeviceCreateRenderPipeline(device.handle(), &descriptor_));
}

} // namespace webgpu
