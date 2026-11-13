#pragma once

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class Adapter;
class SurfaceTexture;

class Surface : public WGPUObject<WGPUSurface, wgpuSurfaceAddRef, wgpuSurfaceRelease> {
public:
  using WGPUObject::WGPUObject;

  WGPUTextureFormat GetPreferredFormat(const Adapter &adapter) const;

  SurfaceTexture GetCurrentTexture() const;

  WGPUStatus Present() const;
};

} // namespace rigel::graphics
