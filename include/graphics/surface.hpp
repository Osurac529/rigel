#pragma once

#include <webgpu/wgpu.h>

namespace rigel::graphics {

class SurfaceConfiguration;
class Adapter;

class Surface {
public:
  explicit Surface(WGPUSurface surface);

  Surface(const Surface &);
  Surface &operator=(const Surface &);

  Surface(Surface &&) = default;
  Surface &operator=(Surface &&) = default;

  ~Surface();

  WGPUTextureFormat GetPreferredFormat(const Adapter &adapter) const;

  WGPUSurfaceTexture GetCurrentTexture() const;

  WGPUStatus Present() const;

  const WGPUSurface &native() const;

private:
  WGPUSurface surface_;
};

} // namespace rigel::graphics
