#pragma once

#include <webgpu/wgpu.h>

#include "graphics/texture.hpp"

namespace rigel::graphics {

class SurfaceTexture {
public:
  explicit SurfaceTexture(WGPUSurfaceTexture surface_texture);

  Texture &texture();

  WGPUSurfaceGetCurrentTextureStatus status() const;

private:
  Texture texture_;
  WGPUSurfaceGetCurrentTextureStatus status_;
};

} // namespace rigel::graphics
