#include "graphics/surface.hpp"

#include "graphics/adapter.hpp"
#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

Surface::Surface(WGPUSurface surface) : surface_(surface) {
  if (!surface_) {
    throw GraphicsException("Surface creation failed.");
  }
}

Surface::Surface(const Surface &other) : surface_(other.surface_) {
  wgpuSurfaceAddRef(surface_);
}

Surface &Surface::operator=(const Surface &other) {
  if (this != &other) {
    surface_ = other.surface_;
    wgpuSurfaceAddRef(surface_);
  }

  return *this;
}

Surface::~Surface() {
  wgpuSurfaceRelease(surface_);
}

WGPUTextureFormat Surface::GetPreferredFormat(const Adapter &adapter) const {
  WGPUSurfaceCapabilities capabilities = WGPU_SURFACE_CAPABILITIES_INIT;

  if (WGPUStatus_Success != wgpuSurfaceGetCapabilities(surface_, adapter.native(), &capabilities)) {
    throw GraphicsException("Failed to get surface capabilities.");
  }

  if (0 == capabilities.formatCount) {
    throw GraphicsException("Failed to get surface format.");
  }

  const auto preferred_format = capabilities.formats[0];
  wgpuSurfaceCapabilitiesFreeMembers(capabilities);

  return preferred_format;
}

WGPUSurfaceTexture Surface::GetCurrentTexture() const {
  WGPUSurfaceTexture surface_texture = WGPU_SURFACE_TEXTURE_INIT;
  wgpuSurfaceGetCurrentTexture(surface_, &surface_texture);

  return surface_texture;
}

WGPUStatus Surface::Present() const {
  return wgpuSurfacePresent(surface_);
}

const WGPUSurface &Surface::native() const {
  return surface_;
}

} // namespace rigel::graphics
