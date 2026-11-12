#include "graphics/command_encoder.hpp"

#include "graphics/command_buffer.hpp"
#include "graphics/graphics_exception.hpp"
#include "graphics/render_pass_encoder.hpp"

namespace rigel::graphics {

CommandEncoder::CommandEncoder(WGPUCommandEncoder command_encoder)
    : command_encoder_(command_encoder) {
  if (!command_encoder_) {
    throw GraphicsException("Failed to create command encoder.");
  }
}

CommandEncoder::CommandEncoder(const CommandEncoder &other)
    : command_encoder_(other.command_encoder_) {
  wgpuCommandEncoderAddRef(command_encoder_);
}

CommandEncoder &CommandEncoder::operator=(const CommandEncoder &other) {
  if (this != &other) {
    command_encoder_ = other.command_encoder_;
    wgpuCommandEncoderAddRef(command_encoder_);
  }

  return *this;
}

CommandEncoder::~CommandEncoder() {
  wgpuCommandEncoderRelease(command_encoder_);
}

RenderPassEncoder
CommandEncoder::BeginRenderPass(const WGPURenderPassDescriptor &render_pass_descriptor) const {
  return RenderPassEncoder(
      wgpuCommandEncoderBeginRenderPass(command_encoder_, &render_pass_descriptor));
}

CommandBuffer
CommandEncoder::Finish(const WGPUCommandBufferDescriptor &command_buffer_descriptor) const {
  return CommandBuffer(wgpuCommandEncoderFinish(command_encoder_, &command_buffer_descriptor));
}

} // namespace rigel::graphics
