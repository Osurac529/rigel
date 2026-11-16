#include "webgpu/render_pass_depth_stencil_attachment_builder.hpp"

#include "webgpu/texture_view.hpp"

namespace webgpu {

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetView(TextureView &texture_view) {
  attachment_.view = texture_view.handle();

  return *this;
}

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetDepthLoadOp(const WGPULoadOp load_op) {
  attachment_.depthLoadOp = load_op;

  return *this;
}

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetDepthStoreOp(const WGPUStoreOp store_op) {
  attachment_.depthStoreOp = store_op;

  return *this;
}

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetDepthClearValue(const float clear_value) {
  attachment_.depthClearValue = clear_value;

  return *this;
}

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetDepthReadOnly(const WGPUBool read_only) {
  attachment_.depthReadOnly = read_only;

  return *this;
}

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetStencilLoadOp(const WGPULoadOp load_op) {
  attachment_.stencilLoadOp = load_op;

  return *this;
}

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetStencilStoreOp(const WGPUStoreOp store_op) {
  attachment_.stencilStoreOp = store_op;

  return *this;
}

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetStencilClearValue(const std::uint32_t clear_value) {
  attachment_.stencilClearValue = clear_value;

  return *this;
}

RenderPassDepthSteniclAttachmentBuilder &
RenderPassDepthSteniclAttachmentBuilder::SetStencilReadOnly(const WGPUBool read_only) {
  attachment_.stencilReadOnly = read_only;

  return *this;
}

const WGPURenderPassDepthStencilAttachment &RenderPassDepthSteniclAttachmentBuilder::Build() {
  return attachment_;
}

} // namespace webgpu
