#include "webgpu/render_pass_encoder_builder.hpp"

#include "webgpu/command_encoder.hpp"
#include "webgpu/render_pass_encoder.hpp"

namespace webgpu {

RenderPassEncoderBuilder &RenderPassEncoderBuilder ::AddRenderPassColorAttachment(
    const RenderPassColorAttachment &render_pass_color_attachment) {
  color_attachments_.push_back(render_pass_color_attachment);
  is_dirty_ = true;

  return *this;
}

RenderPassEncoderBuilder &RenderPassEncoderBuilder::SetRenderPassColorAttachment(
    const std::uint32_t index,
    const RenderPassColorAttachment &render_pass_color_attachment) {
  if (index >= color_attachments_.size()) {
    color_attachments_.resize(index + 1);
  }

  color_attachments_[index] = render_pass_color_attachment;
  is_dirty_ = true;

  return *this;
}

RenderPassEncoderBuilder &RenderPassEncoderBuilder::SetDepthStencilAttachment(
    const RenderPassDepthStencilAttachment &depth_stencil_attachment) {
  depth_stencil_attachment_ = depth_stencil_attachment;
  depth_stencil_attachment_set_ = true;
  is_dirty_ = true;

  return *this;
}

RenderPassEncoder RenderPassEncoderBuilder::Build(const CommandEncoder &command_encoder) {
  if (is_dirty_) {
    is_dirty_ = false;

    webgpu_color_attachments_.clear();
    webgpu_color_attachments_.reserve(color_attachments_.size());

    for (auto &color_attachment : color_attachments_) {
      webgpu_color_attachments_.push_back(color_attachment.Get());
    }

    descriptor_.colorAttachmentCount = webgpu_color_attachments_.size();
    descriptor_.colorAttachments = webgpu_color_attachments_.data();

    if (depth_stencil_attachment_set_) {
      descriptor_.depthStencilAttachment = &depth_stencil_attachment_.Get();
    }
  }

  return RenderPassEncoder(
      wgpuCommandEncoderBeginRenderPass(command_encoder.handle(), &descriptor_));
}

} // namespace webgpu