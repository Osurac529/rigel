#pragma once

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class CommandBuffer;

class Texture : public WGPUObject<WGPUTexture, wgpuTextureAddRef, wgpuTextureRelease> {
public:
  using WGPUObject::WGPUObject;

  WGPUTextureFormat GetFormat() const;
};

} // namespace rigel::graphics
