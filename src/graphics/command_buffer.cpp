#include "graphics/command_buffer.hpp"

#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

CommandBuffer::CommandBuffer(WGPUCommandBuffer command_buffer) : command_buffer_(command_buffer) {
  if (!command_buffer_) {
    throw GraphicsException("Failed to create command buffer.");
  }
}

CommandBuffer::CommandBuffer(const CommandBuffer &other) : command_buffer_(other.command_buffer_) {
  wgpuCommandBufferAddRef(command_buffer_);
}

CommandBuffer &CommandBuffer::operator=(const CommandBuffer &other) {
  if (this != &other) {
    command_buffer_ = other.command_buffer_;
    wgpuCommandBufferAddRef(command_buffer_);
  }

  return *this;
}

CommandBuffer::~CommandBuffer() {
  wgpuCommandBufferRelease(command_buffer_);
}

const WGPUCommandBuffer &CommandBuffer::native() const {
  return command_buffer_;
}

} // namespace rigel::graphics
