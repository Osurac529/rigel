#include "graphics/queue.hpp"

#include "graphics/command_buffer.hpp"
#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

Queue::Queue(WGPUQueue queue) : queue_(queue) {
  if (!queue_) {
    throw GraphicsException("Failed to create queue.");
  }
}

Queue::Queue(const Queue &other) : queue_(other.queue_) {
  wgpuQueueAddRef(queue_);
}

Queue &Queue::operator=(const Queue &other) {
  if (this != &other) {
    queue_ = other.queue_;
    wgpuQueueAddRef(queue_);
  }

  return *this;
}

Queue ::~Queue() {
  wgpuQueueRelease(queue_);
}

void Queue::Submit(const CommandBuffer &command_buffer) const {
  wgpuQueueSubmit(queue_, 1, &command_buffer.native());
}

} // namespace rigel::graphics
