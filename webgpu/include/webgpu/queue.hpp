#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class CommandBuffer;
class Buffer;

class Queue : public Object<WGPUQueue, wgpuQueueAddRef, wgpuQueueRelease> {
public:
  using Object::Object;

  void Submit(const CommandBuffer &command_buffer) const;

  void WriteBuffer(
      const Buffer &buffer,
      void const *data,
      std::size_t size,
      std::uint64_t buffer_offset = 0);

  void WriteBuffer(const Buffer &buffer, void const *data);
};

} // namespace webgpu
