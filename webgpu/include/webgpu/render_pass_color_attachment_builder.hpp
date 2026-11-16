#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

namespace webgpu {

class TextureView;

class RenderPassColorAttachmentBuilder {
public:
  RenderPassColorAttachmentBuilder();

  RenderPassColorAttachmentBuilder &SetView(TextureView &view);

  RenderPassColorAttachmentBuilder &SetDepthSlice(std::uint32_t depth_slice);

  RenderPassColorAttachmentBuilder &SetResolveTarget(TextureView &resolve_target);

  RenderPassColorAttachmentBuilder &SetLoadOp(WGPULoadOp load_op);

  RenderPassColorAttachmentBuilder &SetStoreOp(WGPUStoreOp store_op);

  RenderPassColorAttachmentBuilder &SetClearValue(const WGPUColor &clear_value);

  const WGPURenderPassColorAttachment &Build();

private:
  WGPURenderPassColorAttachment attachment_ = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
};

} // namespace webgpu
