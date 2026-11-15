#include "graphics/render_pipeline_builder.hpp"

#include "graphics/device.hpp"
#include "graphics/fragment_state_builder.hpp"
#include "graphics/render_pipeline.hpp"
#include "graphics/shader_module.hpp"

namespace rigel::graphics {

RenderPipelineBuilder::RenderPipelineBuilder() {
  descriptor_.primitive.cullMode = WGPUCullMode_None;
  descriptor_.primitive.frontFace = WGPUFrontFace_CCW;
  descriptor_.primitive.topology = WGPUPrimitiveTopology_TriangleList;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetVertexShader(
    const ShaderModule &vertex_shader,
    std::string_view entry_point) {
  descriptor_.vertex.module = vertex_shader.native();
  descriptor_.vertex.entryPoint.data = entry_point.data();
  descriptor_.vertex.entryPoint.length = entry_point.length();

  return *this;
}

RenderPipelineBuilder &
RenderPipelineBuilder::SetFragmentState(const FragmentState &fragment_state) {
  fragment_state_ = fragment_state;

  return *this;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetTopology(WGPUPrimitiveTopology topology) {
  descriptor_.primitive.topology = topology;
  return *this;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetCullMode(WGPUCullMode cull_mode) {
  descriptor_.primitive.cullMode = cull_mode;

  return *this;
}

RenderPipelineBuilder &RenderPipelineBuilder::SetFrontFace(WGPUFrontFace front_face) {
  descriptor_.primitive.frontFace = front_face;

  return *this;
}

RenderPipeline RenderPipelineBuilder::Build(Device &device) {
  std::vector<WGPUColorTargetState> targets;
  targets.reserve(fragment_state_.targets_.size());

  for (auto &target : fragment_state_.targets_) {
    target.state_.blend = &target.blend_state_;
    targets.emplace_back(target.state_);
  }

  fragment_state_.state_.targetCount = targets.size();
  fragment_state_.state_.targets = targets.data();
  descriptor_.fragment = &fragment_state_.state_;

  return RenderPipeline(device, descriptor_);
}

} // namespace rigel::graphics
