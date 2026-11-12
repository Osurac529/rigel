#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class RenderPassEncoder;
class CommandBuffer;

class CommandEncoder
    : public WGPUObject<WGPUCommandEncoder, wgpuCommandEncoderAddRef, wgpuCommandEncoderRelease> {
public:
  using WGPUObject::WGPUObject;

  RenderPassEncoder BeginRenderPass(
      const WGPURenderPassDescriptor &render_pass_descriptor =
          WGPU_RENDER_PASS_DESCRIPTOR_INIT) const;

  CommandBuffer Finish(
      const WGPUCommandBufferDescriptor &command_buffer_descriptor =
          WGPU_COMMAND_BUFFER_DESCRIPTOR_INIT) const;
};

} // namespace rigel::graphics
