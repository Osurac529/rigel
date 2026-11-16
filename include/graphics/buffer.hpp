#pragma once

#include <cstdint>
#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class Device;
class Queue;

class Buffer : public WGPUObject<WGPUBuffer, wgpuBufferAddRef, wgpuBufferRelease> {
public:
  using WGPUObject::WGPUObject;

  explicit Buffer(Device &device, const WGPUBufferDescriptor &descriptor);

  uint64_t GetSize() const;
};

class IndexBuffer : public Buffer {
public:
  explicit IndexBuffer(Device &device, const std::vector<std::uint16_t> &indices);

  explicit IndexBuffer(Device &device, Queue& queue, const std::vector<std::uint16_t> &indices);

  explicit IndexBuffer(Device &device, const std::vector<std::uint32_t> &indices);

  explicit IndexBuffer(Device &device, Queue &queue, const std::vector<std::uint32_t> &indices);

  WGPUIndexFormat format() const;

private:
  WGPUIndexFormat format_;
};

} // namespace rigel::graphics
