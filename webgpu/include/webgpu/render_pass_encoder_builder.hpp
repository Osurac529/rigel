#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/render_pass_color_attachment_builder.hpp"
#include "webgpu/render_pass_depth_stencil_attachment_builder.hpp"

namespace webgpu {

class RenderPassEncoder;
class CommandEncoder;

class RenderPassEncoderBuilder {
public:
  RenderPassEncoderBuilder &
  AddRenderPassColorAttachment(const RenderPassColorAttachment &render_pass_color_attachment);

  RenderPassEncoderBuilder &
  SetDepthStencilAttachment(const RenderPassDepthStencilAttachment &depth_stencil_attachment);

  RenderPassEncoder Build(CommandEncoder &command_encoder);

private:
  bool depth_stencil_attachment_set_ = false;
  std::vector<RenderPassColorAttachment> color_attachments_;
  RenderPassDepthStencilAttachment depth_stencil_attachment_;
  WGPURenderPassDescriptor descriptor_ = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
};

} // namespace webgpu
