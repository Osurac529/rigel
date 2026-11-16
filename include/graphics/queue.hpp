#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class CommandBuffer;
class Buffer;

class Queue : public WGPUObject<WGPUQueue, wgpuQueueAddRef, wgpuQueueRelease> {
public:
  using WGPUObject::WGPUObject;

  void Submit(const CommandBuffer &command_buffer) const;

  void WriteBuffer(
      const Buffer &buffer,
      void const *data,
      std::size_t size,
      std::uint64_t buffer_offset = 0);

  void WriteBuffer(const Buffer &buffer, void const *data);
};

} // namespace rigel::graphics
