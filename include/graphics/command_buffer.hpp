#pragma once

#include <webgpu/wgpu.h>

namespace rigel::graphics {

class CommandBuffer {
public:
  explicit CommandBuffer(WGPUCommandBuffer command_buffer);

  CommandBuffer(const CommandBuffer &);
  CommandBuffer &operator=(const CommandBuffer &);

  CommandBuffer(CommandBuffer &&) = default;
  CommandBuffer &operator=(CommandBuffer &&) = default;

  ~CommandBuffer();

  const WGPUCommandBuffer& native() const;

private:
  WGPUCommandBuffer command_buffer_;
};

} // namespace rigel::graphics
