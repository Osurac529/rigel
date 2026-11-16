#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/texture.hpp"

namespace webgpu {

class SurfaceTexture {
public:
  explicit SurfaceTexture(const WGPUSurfaceTexture &surface_texture);

  Texture &texture();

  WGPUSurfaceGetCurrentTextureStatus status() const;

private:
  Texture texture_;
  WGPUSurfaceGetCurrentTextureStatus status_;
};

} // namespace webgpu
