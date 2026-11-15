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

  void
  WriteBuffer(const Buffer &buffer, std::uint64_t bufferOffset, void const *data, std::size_t size);
};

} // namespace rigel::graphics
