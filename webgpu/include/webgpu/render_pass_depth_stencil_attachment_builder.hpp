#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

namespace webgpu {

class TextureView;

class RenderPassDepthSteniclAttachmentBuilder {
public:
  RenderPassDepthSteniclAttachmentBuilder &SetView(TextureView &texture_view);

  RenderPassDepthSteniclAttachmentBuilder &SetDepthLoadOp(WGPULoadOp load_op);

  RenderPassDepthSteniclAttachmentBuilder &SetDepthStoreOp(WGPUStoreOp store_op);

  RenderPassDepthSteniclAttachmentBuilder &SetDepthClearValue(float clear_value);

  RenderPassDepthSteniclAttachmentBuilder &SetDepthReadOnly(WGPUBool read_only);

  RenderPassDepthSteniclAttachmentBuilder &SetStencilLoadOp(WGPULoadOp load_op);

  RenderPassDepthSteniclAttachmentBuilder &SetStencilStoreOp(WGPUStoreOp store_op);

  RenderPassDepthSteniclAttachmentBuilder &SetStencilClearValue(std::uint32_t clear_value);

  RenderPassDepthSteniclAttachmentBuilder &SetStencilReadOnly(WGPUBool read_only);

  const WGPURenderPassDepthStencilAttachment &Build();

private:
  WGPURenderPassDepthStencilAttachment attachment_ = WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT;
};

} // namespace webgpu
