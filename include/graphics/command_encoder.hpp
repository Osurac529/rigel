#pragma once

#include <vector>

#include <webgpu/wgpu.h>

namespace rigel::graphics {

class RenderPassEncoder;
class CommandBuffer;

class CommandEncoder {
public:
  explicit CommandEncoder(WGPUCommandEncoder command_encoder);

  CommandEncoder(const CommandEncoder &);
  CommandEncoder &operator=(const CommandEncoder &);

  CommandEncoder(CommandEncoder &&) = default;
  CommandEncoder &operator=(CommandEncoder &&) = default;

  ~CommandEncoder();

  RenderPassEncoder BeginRenderPass(
      const WGPURenderPassDescriptor &render_pass_descriptor =
          WGPU_RENDER_PASS_DESCRIPTOR_INIT) const;

  CommandBuffer Finish(
      const WGPUCommandBufferDescriptor &command_buffer_descriptor =
          WGPU_COMMAND_BUFFER_DESCRIPTOR_INIT) const;

private:
  WGPUCommandEncoder command_encoder_;
};

} // namespace rigel::graphics
