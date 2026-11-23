#include "webgpu/render_pass_depth_stencil_attachment_builder.hpp"

namespace webgpu {

RenderPassDepthStencilAttachmentBuilder::RenderPassDepthStencilAttachmentBuilder() {
  attachment_.depthLoadOp = WGPULoadOp_Clear;
  attachment_.depthStoreOp = WGPUStoreOp_Store;
  attachment_.depthClearValue = 1.0f;
}

RenderPassDepthStencilAttachment::RenderPassDepthStencilAttachment(
    const TextureView &view,
    const WGPURenderPassDepthStencilAttachment &attachment)
    : view_(view), attachment_(attachment) {}

const WGPURenderPassDepthStencilAttachment &RenderPassDepthStencilAttachment::Get() {
  attachment_.view = view_.handle();

  return attachment_;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetView(const TextureView &texture_view) {
  is_dirty_ = true;
  view_ = texture_view;

  return *this;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetDepthLoadOp(const WGPULoadOp load_op) {
  is_dirty_ = is_dirty_ || attachment_.depthLoadOp != load_op;
  attachment_.depthLoadOp = load_op;

  return *this;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetDepthStoreOp(const WGPUStoreOp store_op) {
  is_dirty_ = is_dirty_ || attachment_.depthStoreOp != store_op;
  attachment_.depthStoreOp = store_op;

  return *this;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetDepthClearValue(const float clear_value) {
  is_dirty_ = is_dirty_ || attachment_.depthClearValue != clear_value;
  attachment_.depthClearValue = clear_value;

  return *this;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetDepthReadOnly(const WGPUBool read_only) {
  is_dirty_ = is_dirty_ || attachment_.depthReadOnly != read_only;
  attachment_.depthReadOnly = read_only;

  return *this;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetStencilLoadOp(const WGPULoadOp load_op) {
  is_dirty_ = is_dirty_ || attachment_.stencilLoadOp != load_op;
  attachment_.stencilLoadOp = load_op;

  return *this;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetStencilStoreOp(const WGPUStoreOp store_op) {
  is_dirty_ = is_dirty_ || attachment_.stencilStoreOp != store_op;
  attachment_.stencilStoreOp = store_op;

  return *this;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetStencilClearValue(const std::uint32_t clear_value) {
  is_dirty_ = is_dirty_ || attachment_.stencilClearValue != clear_value;
  attachment_.stencilClearValue = clear_value;

  return *this;
}

RenderPassDepthStencilAttachmentBuilder &
RenderPassDepthStencilAttachmentBuilder::SetStencilReadOnly(const WGPUBool read_only) {
  is_dirty_ = is_dirty_ || attachment_.stencilReadOnly != read_only;
  attachment_.stencilReadOnly = read_only;

  return *this;
}

RenderPassDepthStencilAttachment RenderPassDepthStencilAttachmentBuilder::Build() const {
  is_dirty_ = false;

  return RenderPassDepthStencilAttachment(view_, attachment_);
}

bool RenderPassDepthStencilAttachmentBuilder::IsDirty() const {
  return is_dirty_;
}

} // namespace webgpu
