#include "graphics/command_encoder.hpp"

#include "graphics/command_buffer.hpp"
#include "graphics/render_pass_encoder.hpp"

namespace rigel::graphics {

RenderPassEncoder
CommandEncoder::BeginRenderPass(const WGPURenderPassDescriptor &descriptor) const {
  return RenderPassEncoder(wgpuCommandEncoderBeginRenderPass(native(), &descriptor));
}

CommandBuffer CommandEncoder::Finish(const WGPUCommandBufferDescriptor &descriptor) const {
  return CommandBuffer(wgpuCommandEncoderFinish(native(), &descriptor));
}

} // namespace rigel::graphics
