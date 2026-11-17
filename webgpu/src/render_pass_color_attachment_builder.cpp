#include "webgpu/render_pass_color_attachment_builder.hpp"

namespace webgpu {

RenderPassColorAttachment::RenderPassColorAttachment(
    const TextureView &view,
    const TextureView &resolve_target,
    const WGPURenderPassColorAttachment &attachment)
    : view_(view), resolve_target_(resolve_target), attachment_(attachment) {}

const WGPURenderPassColorAttachment &RenderPassColorAttachment::Get() {
  attachment_.view = view_.handle();
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
RenderPassColorAttachmentBuilder::SetView(const TextureView &view) {
  view_ = view;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetDepthSlice(const std::uint32_t depth_slice) {
  attachment_.depthSlice = depth_slice;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetResolveTarget(const TextureView &resolve_target) {
  resolve_target_ = resolve_target;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetLoadOp(const WGPULoadOp load_op) {
  attachment_.loadOp = load_op;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetStoreOp(const WGPUStoreOp store_op) {
  attachment_.storeOp = store_op;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetClearValue(const WGPUColor &clear_value) {
  attachment_.clearValue = clear_value;

  return *this;
}

RenderPassColorAttachment RenderPassColorAttachmentBuilder::Build() const {
  return RenderPassColorAttachment(view_, resolve_target_, attachment_);
}

} // namespace webgpu
