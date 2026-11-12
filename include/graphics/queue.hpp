#pragma once

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class CommandBuffer;

class Queue : public WGPUObject<WGPUQueue, wgpuQueueAddRef, wgpuQueueRelease> {
public:
  using WGPUObject::WGPUObject;

  void Submit(const CommandBuffer &command_buffer) const;
};

} // namespace rigel::graphics
