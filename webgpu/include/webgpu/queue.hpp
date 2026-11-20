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

  void WriteTexture(
      const WGPUTexelCopyTextureInfo &destination,
      const void *data,
      size_t data_size,
      const WGPUTexelCopyBufferLayout &data_layout,
      const WGPUExtent3D &write_size);
};

} // namespace webgpu
