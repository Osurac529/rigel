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
      Device &device,
      WGPUBufferUsage usage,
      std::uint64_t size,
      WGPUBool mappedAtCreation);

  uint64_t GetSize() const;
};

} // namespace webgpu
