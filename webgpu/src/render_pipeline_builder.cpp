#include "webgpu/render_pipeline_builder.hpp"

#include "webgpu/device.hpp"
#include "webgpu/fragment_state_builder.hpp"
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

RenderPipeline RenderPipelineBuilder::Build(Device &device) {
  // link up fragment
  std::vector<WGPUColorTargetState> targets;
  targets.reserve(fragment_state_.targets_.size());

  for (auto &target : fragment_state_.targets_) {
    target.state_.blend = &target.blend_state_;
    targets.emplace_back(target.state_);
  }

  fragment_state_.state_.targetCount = targets.size();
  fragment_state_.state_.targets = targets.data();
  descriptor_.fragment = &fragment_state_.state_;

  // link up vertex
  descriptor_.vertex = vertex_state_.state_;

  std::vector<WGPUVertexBufferLayout> buffer_layouts;
  buffer_layouts.reserve(vertex_state_.buffer_layouts_.size());

  for (const auto &buffer_layout : vertex_state_.buffer_layouts_) {
    WGPUVertexBufferLayout layout = buffer_layout.layout_;
    layout.attributeCount = buffer_layout.attributes_.size();
    layout.attributes = buffer_layout.attributes_.data();

    buffer_layouts.push_back(layout);
  }

  descriptor_.vertex.bufferCount = buffer_layouts.size();
  descriptor_.vertex.buffers = buffer_layouts.data();

  return RenderPipeline(wgpuDeviceCreateRenderPipeline(device.handle(), &descriptor_));
}

} // namespace webgpu
