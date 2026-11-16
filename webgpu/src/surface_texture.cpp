#include "webgpu/surface_texture.hpp"

namespace webgpu {

SurfaceTexture::SurfaceTexture(const WGPUSurfaceTexture &surface_texture)
    : texture_(surface_texture.texture), status_(surface_texture.status) {}

Texture &SurfaceTexture::texture() {
  return texture_;
}

WGPUSurfaceGetCurrentTextureStatus SurfaceTexture::status() const {
  return status_;
}

} // namespace webgpu
