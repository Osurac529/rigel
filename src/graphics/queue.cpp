#include "graphics/queue.hpp"

#include "graphics/buffer.hpp"
#include "graphics/command_buffer.hpp"

namespace rigel::graphics {

void Queue::Submit(const CommandBuffer &command_buffer) const {
  wgpuQueueSubmit(native(), 1, &command_buffer.native());
}

void Queue::WriteBuffer(
    const Buffer &buffer,
    const std::uint64_t buffer_offset,
    void const *const data,
    const std::size_t size) {
  wgpuQueueWriteBuffer(native(), buffer.native(), buffer_offset, data, size);
}

} // namespace rigel::graphics
