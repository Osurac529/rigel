#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

#include "webgpu/texture_view.hpp"

namespace webgpu {

class RenderPassColorAttachment {
public:
  RenderPassColorAttachment() = default;

  explicit RenderPassColorAttachment(
      const TextureView &view,
      const TextureView &resolve_target,
      const WGPURenderPassColorAttachment &attachment);

  const WGPURenderPassColorAttachment &Get();

private:
  TextureView view_;
  TextureView resolve_target_;
  WGPURenderPassColorAttachment attachment_ = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
};

class RenderPassColorAttachmentBuilder {
public:
  RenderPassColorAttachmentBuilder();

  RenderPassColorAttachmentBuilder &SetView(const TextureView &view);

  RenderPassColorAttachmentBuilder &SetDepthSlice(std::uint32_t depth_slice);

  RenderPassColorAttachmentBuilder &SetResolveTarget(const TextureView &resolve_target);

  RenderPassColorAttachmentBuilder &SetLoadOp(WGPULoadOp load_op);

  RenderPassColorAttachmentBuilder &SetStoreOp(WGPUStoreOp store_op);

  RenderPassColorAttachmentBuilder &SetClearValue(const WGPUColor &clear_value);

  RenderPassColorAttachment Build() const;

private:
  TextureView view_;
  TextureView resolve_target_;
  WGPURenderPassColorAttachment attachment_ = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
};

} // namespace webgpu
