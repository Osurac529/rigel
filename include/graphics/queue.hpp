#pragma once

#include <webgpu/wgpu.h>

namespace rigel::graphics {

class CommandBuffer;

class Queue {
public:
  explicit Queue(WGPUQueue queue);

  Queue(const Queue &);
  Queue &operator=(const Queue &);

  Queue(Queue &&) = default;
  Queue &operator=(Queue &&) = default;

  ~Queue();

  void Submit(const CommandBuffer &command_buffer) const;

private:
  WGPUQueue queue_;
};

} // namespace rigel::graphics
