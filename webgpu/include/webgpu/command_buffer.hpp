#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class CommandBuffer
    : public Object<WGPUCommandBuffer, wgpuCommandBufferAddRef, wgpuCommandBufferRelease> {
public:
  using Object::Object;
};

} // namespace webgpu
