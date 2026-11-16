#include "webgpu/render_pass_encoder_builder.hpp"

#include "webgpu/command_encoder.hpp"
#include "webgpu/render_pass_encoder.hpp"

namespace webgpu {

RenderPassEncoderBuilder &RenderPassEncoderBuilder ::AddRenderPassColorAttachment(
    const WGPURenderPassColorAttachment &render_pass_color_attachment) {
  color_attachments_.push_back(render_pass_color_attachment);

  return *this;
}

RenderPassEncoderBuilder &RenderPassEncoderBuilder::SetDepthStencilAttachment(
    const WGPURenderPassDepthStencilAttachment &depth_stencil_attachment) {
  depth_stencil_attachment_ = depth_stencil_attachment;

  return *this;
}

// RenderPassEncoderBuilder &SetOcclusionQuerySet(OcclusionQuerySet &occlusion_query_set);

RenderPassEncoder RenderPassEncoderBuilder::Build(CommandEncoder &command_encoder) {
  descriptor_.colorAttachmentCount = color_attachments_.size();
  descriptor_.colorAttachments = color_attachments_.data();
  descriptor_.depthStencilAttachment = &depth_stencil_attachment_;

  return RenderPassEncoder(
      wgpuCommandEncoderBeginRenderPass(command_encoder.handle(), &descriptor_));
}

} // namespace webgpu