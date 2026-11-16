#include "webgpu/queue.hpp"

#include "webgpu/buffer.hpp"
#include "webgpu/command_buffer.hpp"

namespace webgpu {

void Queue::Submit(const CommandBuffer &command_buffer) const {
  wgpuQueueSubmit(handle(), 1, &command_buffer.handle());
}

void Queue::WriteBuffer(
    const Buffer &buffer,
    void const *const data,
    const std::size_t size,
    const std::uint64_t buffer_offset) {
  wgpuQueueWriteBuffer(handle(), buffer.handle(), buffer_offset, data, size);
}

void Queue::WriteBuffer(const Buffer &buffer, void const *const data) {
  wgpuQueueWriteBuffer(handle(), buffer.handle(), 0, data, buffer.GetSize());
}

} // namespace webgpu
