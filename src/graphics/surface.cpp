#include "graphics/surface.hpp"

#include "graphics/adapter.hpp"
#include "graphics/graphics_exception.hpp"
#include "graphics/surface_texture.hpp"

namespace rigel::graphics {

WGPUTextureFormat Surface::GetPreferredFormat(const Adapter &adapter) const {
  WGPUSurfaceCapabilities capabilities = WGPU_SURFACE_CAPABILITIES_INIT;

  if (WGPUStatus_Success != wgpuSurfaceGetCapabilities(native(), adapter.native(), &capabilities)) {
    throw GraphicsException("Failed to get surface capabilities.");
  }

  if (0 == capabilities.formatCount) {
    throw GraphicsException("Failed to get surface format.");
  }

  const auto preferred_format = capabilities.formats[0];
  wgpuSurfaceCapabilitiesFreeMembers(capabilities);

  return preferred_format;
}

SurfaceTexture Surface::GetCurrentTexture() const {
  WGPUSurfaceTexture surface_texture = WGPU_SURFACE_TEXTURE_INIT;
  wgpuSurfaceGetCurrentTexture(native(), &surface_texture);

  return SurfaceTexture(surface_texture);
}

WGPUStatus Surface::Present() const {
  return wgpuSurfacePresent(native());
}

} // namespace rigel::graphics
