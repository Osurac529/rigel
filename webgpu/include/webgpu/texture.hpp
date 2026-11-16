#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class Texture : public Object<WGPUTexture, wgpuTextureAddRef, wgpuTextureRelease> {
public:
  using Object::Object;

  WGPUTextureFormat GetFormat() const;
};

} // namespace webgpu
