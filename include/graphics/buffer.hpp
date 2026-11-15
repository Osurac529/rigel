#pragma once

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class Device;

class Buffer : public WGPUObject<WGPUBuffer, wgpuBufferAddRef, wgpuBufferRelease> {
public:
  using WGPUObject::WGPUObject;

  explicit Buffer(Device &device, const WGPUBufferDescriptor &descriptor);

  uint64_t GetSize() const;
};

} // namespace rigel::graphics
