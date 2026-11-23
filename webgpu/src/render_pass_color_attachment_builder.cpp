#include "webgpu/render_pass_color_attachment_builder.hpp"

namespace webgpu {

RenderPassColorAttachment::RenderPassColorAttachment(
    const TextureView &view,
    const TextureView &resolve_target,
    const WGPURenderPassColorAttachment &attachment)
    : view_(view), resolve_target_(resolve_target), attachment_(attachment) {}

RenderPassColorAttachment::RenderPassColorAttachment(
    const WGPUTextureView &view,
    const TextureView &resolve_target,
    const WGPURenderPassColorAttachment &attachment)
    : weak_view_(view), resolve_target_(resolve_target), attachment_(attachment) {}

const WGPURenderPassColorAttachment &RenderPassColorAttachment::Get() {
  attachment_.view = view_ ? view_.handle() : weak_view_;
  attachment_.resolveTarget = resolve_target_.handle();

  return attachment_;
}

RenderPassColorAttachmentBuilder::RenderPassColorAttachmentBuilder() {
  attachment_.loadOp = WGPULoadOp_Clear;
  attachment_.storeOp = WGPUStoreOp_Store;
  attachment_.clearValue.r = 0.0;
  attachment_.clearValue.g = 0.0;
  attachment_.clearValue.b = 0.0;
  attachment_.clearValue.a = 1.0;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetView(const WGPUTextureView &view) {
  is_dirty_ = true;
  view_ = TextureView();
  weak_view_ = view;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetView(const TextureView &view) {
  is_dirty_ = true;
  view_ = view;
  weak_view_ = nullptr;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetDepthSlice(const std::uint32_t depth_slice) {
  is_dirty_ = is_dirty_ || attachment_.depthSlice != depth_slice;
  attachment_.depthSlice = depth_slice;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetResolveTarget(const TextureView &resolve_target) {
  is_dirty_ = true;
  resolve_target_ = resolve_target;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetLoadOp(const WGPULoadOp load_op) {
  is_dirty_ = is_dirty_ || attachment_.loadOp != load_op;
  attachment_.loadOp = load_op;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetStoreOp(const WGPUStoreOp store_op) {
  is_dirty_ = is_dirty_ || attachment_.storeOp != store_op;
  attachment_.storeOp = store_op;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetClearValue(const WGPUColor &clear_value) {
  is_dirty_ = is_dirty_ || attachment_.clearValue.r != clear_value.r ||
              attachment_.clearValue.g != clear_value.g ||
              attachment_.clearValue.b != clear_value.b ||
              attachment_.clearValue.a != clear_value.a;
  attachment_.clearValue = clear_value;

  return *this;
}

RenderPassColorAttachment RenderPassColorAttachmentBuilder::Build() const {
  is_dirty_ = false;

  if (weak_view_) {
    return RenderPassColorAttachment(weak_view_, resolve_target_, attachment_);
  }

  return RenderPassColorAttachment(view_, resolve_target_, attachment_);
}

bool RenderPassColorAttachmentBuilder::IsDirty() const {
  return is_dirty_;
}

} // namespace webgpu
