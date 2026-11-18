#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

#include "webgpu/texture_view.hpp"

namespace webgpu {

class RenderPassDepthStencilAttachment {
public:
  RenderPassDepthStencilAttachment() = default;

  explicit RenderPassDepthStencilAttachment(
      const TextureView &view,
      const WGPURenderPassDepthStencilAttachment &attachment);

  const WGPURenderPassDepthStencilAttachment &Get();

private:
  TextureView view_;
  WGPURenderPassDepthStencilAttachment attachment_ = WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT;
};

class RenderPassDepthStencilAttachmentBuilder {
public:
  RenderPassDepthStencilAttachmentBuilder();

  RenderPassDepthStencilAttachmentBuilder &SetView(const TextureView &texture_view);

  RenderPassDepthStencilAttachmentBuilder &SetDepthLoadOp(WGPULoadOp load_op);

  RenderPassDepthStencilAttachmentBuilder &SetDepthStoreOp(WGPUStoreOp store_op);

  RenderPassDepthStencilAttachmentBuilder &SetDepthClearValue(float clear_value);

  RenderPassDepthStencilAttachmentBuilder &SetDepthReadOnly(WGPUBool read_only);

  RenderPassDepthStencilAttachmentBuilder &SetStencilLoadOp(WGPULoadOp load_op);

  RenderPassDepthStencilAttachmentBuilder &SetStencilStoreOp(WGPUStoreOp store_op);

  RenderPassDepthStencilAttachmentBuilder &SetStencilClearValue(std::uint32_t clear_value);

  RenderPassDepthStencilAttachmentBuilder &SetStencilReadOnly(WGPUBool read_only);

  RenderPassDepthStencilAttachment Build() const;

private:
  TextureView view_;
  WGPURenderPassDepthStencilAttachment attachment_ = WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT;
};

} // namespace webgpu
