#include "webgpu/render_pass_encoder_builder.hpp"

#include "webgpu/command_encoder.hpp"
#include "webgpu/render_pass_encoder.hpp"

namespace webgpu {

RenderPassEncoderBuilder &RenderPassEncoderBuilder ::AddRenderPassColorAttachment(
    const RenderPassColorAttachment &render_pass_color_attachment) {
  color_attachments_.push_back(render_pass_color_attachment);

  return *this;
}

RenderPassEncoderBuilder &RenderPassEncoderBuilder::SetDepthStencilAttachment(
    const RenderPassDepthStencilAttachment &depth_stencil_attachment) {
  depth_stencil_attachment_ = depth_stencil_attachment;
  depth_stencil_attachment_set_ = true;

  return *this;
}

RenderPassEncoder RenderPassEncoderBuilder::Build(CommandEncoder &command_encoder) {
  std::vector<WGPURenderPassColorAttachment> color_attachments;
  color_attachments.reserve(color_attachments_.size());

  for (auto &color_attachment : color_attachments_) {
    color_attachments.push_back(color_attachment.Get());
  }

  descriptor_.colorAttachmentCount = color_attachments.size();
  descriptor_.colorAttachments = color_attachments.data();

  if (depth_stencil_attachment_set_) {
    descriptor_.depthStencilAttachment = &depth_stencil_attachment_.Get();
  }

  return RenderPassEncoder(
      wgpuCommandEncoderBeginRenderPass(command_encoder.handle(), &descriptor_));
}

} // namespace webgpu