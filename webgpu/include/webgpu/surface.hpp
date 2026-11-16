#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class Adapter;
class SurfaceTexture;
class Instance;

class Surface : public Object<WGPUSurface, wgpuSurfaceAddRef, wgpuSurfaceRelease> {
public:
  using Object::Object;

  explicit Surface(Instance &instance, void *hwnd, void *hinstance);

  WGPUTextureFormat GetPreferredFormat(const Adapter &adapter) const;

  SurfaceTexture GetCurrentTexture() const;

  WGPUStatus Present() const;
};

} // namespace webgpu
