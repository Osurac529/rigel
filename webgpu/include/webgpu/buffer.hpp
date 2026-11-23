#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class Device;

class Buffer : public Object<WGPUBuffer, wgpuBufferAddRef, wgpuBufferRelease> {
public:
  using Object::Object;

  explicit Buffer(
      const Device &device,
      WGPUBufferUsage usage,
      std::uint64_t size,
      WGPUBool mapped_at_creation = WGPU_FALSE);

  uint64_t GetSize() const;

  WGPUBufferUsage GetUsage() const;
};

} // namespace webgpu
