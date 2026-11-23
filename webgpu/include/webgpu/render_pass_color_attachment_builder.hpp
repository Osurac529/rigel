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

  explicit RenderPassColorAttachment(
      const WGPUTextureView &view,
      const TextureView &resolve_target,
      const WGPURenderPassColorAttachment &attachment);

  const WGPURenderPassColorAttachment &Get();

private:
  WGPUTextureView weak_view_ = nullptr;
  TextureView view_;
  TextureView resolve_target_;
  WGPURenderPassColorAttachment attachment_ = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
};

class RenderPassColorAttachmentBuilder {
public:
  RenderPassColorAttachmentBuilder();

  RenderPassColorAttachmentBuilder &SetView(const WGPUTextureView &view);

  RenderPassColorAttachmentBuilder &SetView(const TextureView &view);

  RenderPassColorAttachmentBuilder &SetDepthSlice(std::uint32_t depth_slice);

  RenderPassColorAttachmentBuilder &SetResolveTarget(const TextureView &resolve_target);

  RenderPassColorAttachmentBuilder &SetLoadOp(WGPULoadOp load_op);

  RenderPassColorAttachmentBuilder &SetStoreOp(WGPUStoreOp store_op);

  RenderPassColorAttachmentBuilder &SetClearValue(const WGPUColor &clear_value);

  RenderPassColorAttachment Build() const;

  bool IsDirty() const;

private:
  WGPUTextureView weak_view_ = nullptr;
  TextureView view_;
  TextureView resolve_target_;
  WGPURenderPassColorAttachment attachment_ = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
  mutable bool is_dirty_ = true;
};

} // namespace webgpu
