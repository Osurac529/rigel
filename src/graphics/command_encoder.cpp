#include "graphics/command_encoder.hpp"

#include "graphics/command_buffer.hpp"
#include "graphics/render_pass_encoder.hpp"

namespace rigel::graphics {

RenderPassEncoder
CommandEncoder::BeginRenderPass(const WGPURenderPassDescriptor &render_pass_descriptor) const {
  return RenderPassEncoder(wgpuCommandEncoderBeginRenderPass(native(), &render_pass_descriptor));
}

CommandBuffer
CommandEncoder::Finish(const WGPUCommandBufferDescriptor &command_buffer_descriptor) const {
  return CommandBuffer(wgpuCommandEncoderFinish(native(), &command_buffer_descriptor));
}

} // namespace rigel::graphics
