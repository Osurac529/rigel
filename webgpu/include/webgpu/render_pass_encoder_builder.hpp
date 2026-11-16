#pragma once

#include <vector>

#include <webgpu/wgpu.h>

namespace webgpu {

class RenderPassEncoder;
class TextureView;
class CommandEncoder;
// class OcclusionQuerySet;

class RenderPassEncoderBuilder {
public:
  RenderPassEncoderBuilder &
  AddRenderPassColorAttachment(const WGPURenderPassColorAttachment &render_pass_color_attachment);

  RenderPassEncoderBuilder &
  SetDepthStencilAttachment(const WGPURenderPassDepthStencilAttachment &depth_stencil_attachment);

  // RenderPassEncoderBuilder &SetOcclusionQuerySet(OcclusionQuerySet &occlusion_query_set);

  RenderPassEncoder Build(CommandEncoder& command_encoder);

private:
  bool depth_stencil_attachment_set_ = false;
  std::vector<WGPURenderPassColorAttachment> color_attachments_;
  WGPURenderPassDepthStencilAttachment depth_stencil_attachment_ =
      WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT;
  WGPURenderPassDescriptor descriptor_ = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
};

} // namespace webgpu
