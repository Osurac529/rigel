#include "graphics/queue.hpp"

#include "graphics/buffer.hpp"
#include "graphics/command_buffer.hpp"

namespace rigel::graphics {

void Queue::Submit(const CommandBuffer &command_buffer) const {
  wgpuQueueSubmit(native(), 1, &command_buffer.native());
}

void Queue::WriteBuffer(
    const Buffer &buffer,
    void const *const data,
    const std::size_t size,
    const std::uint64_t buffer_offset) {
  wgpuQueueWriteBuffer(native(), buffer.native(), buffer_offset, data, size);
}

void Queue::WriteBuffer(const Buffer &buffer, void const *const data) {
  wgpuQueueWriteBuffer(native(), buffer.native(), 0, data, buffer.GetSize());
}

} // namespace rigel::graphics
