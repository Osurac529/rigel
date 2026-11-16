#include "webgpu/render_pass_color_attachment_builder.hpp"

#include "webgpu/texture_view.hpp"

namespace webgpu {

RenderPassColorAttachmentBuilder::RenderPassColorAttachmentBuilder() {
  attachment_.loadOp = WGPULoadOp_Clear;
  attachment_.storeOp = WGPUStoreOp_Store;
  attachment_.clearValue.r = 0.0;
  attachment_.clearValue.g = 0.0;
  attachment_.clearValue.b = 0.0;
  attachment_.clearValue.a = 1.0;

}

RenderPassColorAttachmentBuilder &RenderPassColorAttachmentBuilder::SetView(TextureView &view) {
  attachment_.view = view.handle();

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetDepthSlice(const std::uint32_t depth_slice) {
  attachment_.depthSlice = depth_slice;

  return *this;
}

RenderPassColorAttachmentBuilder &
RenderPassColorAttachmentBuilder::SetResolveTarget(TextureView &resolve_target) {
  attachment_.resolveTarget = resolve_target.handle();

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

const WGPURenderPassColorAttachment &RenderPassColorAttachmentBuilder::Build() {
  return attachment_;
}

} // namespace webgpu