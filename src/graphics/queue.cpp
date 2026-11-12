#include "graphics/queue.hpp"

#include "graphics/command_buffer.hpp"

namespace rigel::graphics {

void Queue::Submit(const CommandBuffer &command_buffer) const {
  wgpuQueueSubmit(native(), 1, &command_buffer.native());
}

} // namespace rigel::graphics
