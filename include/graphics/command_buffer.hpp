#pragma once

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class CommandBuffer
    : public WGPUObject<WGPUCommandBuffer, wgpuCommandBufferAddRef, wgpuCommandBufferRelease> {
public:
  using WGPUObject::WGPUObject;
};

} // namespace rigel::graphics
