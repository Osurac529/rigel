#include "webgpu/surface.hpp"

#include "webgpu/adapter.hpp"
#include "webgpu/exception.hpp"
#include "webgpu/instance.hpp"
#include "webgpu/surface_texture.hpp"

namespace webgpu {

namespace {

WGPUSurface Create(Instance &instance, void *hwnd, void *hinstance) {
  WGPUSurfaceSourceWindowsHWND source = WGPU_SURFACE_SOURCE_WINDOWS_HWND_INIT;

  source.chain.sType = WGPUSType_SurfaceSourceWindowsHWND;
  source.hinstance = hinstance;
  source.hwnd = hwnd;

  WGPUSurfaceDescriptor surface_descriptor = WGPU_SURFACE_DESCRIPTOR_INIT;
  surface_descriptor.nextInChain = &source.chain;

  return wgpuInstanceCreateSurface(instance.handle(), &surface_descriptor);
}

} // namespace

Surface::Surface(Instance &instance, void *hwnd, void *hinstance)
    : Surface(Create(instance, hwnd, hinstance)) {}

WGPUTextureFormat Surface::GetPreferredFormat(const Adapter &adapter) const {
  WGPUSurfaceCapabilities capabilities = WGPU_SURFACE_CAPABILITIES_INIT;

  if (WGPUStatus_Success != wgpuSurfaceGetCapabilities(handle(), adapter.handle(), &capabilities)) {
    throw Exception("Failed to get surface capabilities.");
  }

  if (0 == capabilities.formatCount) {
    throw Exception("Failed to get surface format.");
  }

  const auto preferred_format = capabilities.formats[0];
  wgpuSurfaceCapabilitiesFreeMembers(capabilities);

  return preferred_format;
}

SurfaceTexture Surface::GetCurrentTexture() const {
  WGPUSurfaceTexture surface_texture = WGPU_SURFACE_TEXTURE_INIT;
  wgpuSurfaceGetCurrentTexture(handle(), &surface_texture);

  return SurfaceTexture(surface_texture);
}

WGPUStatus Surface::Present() const {
  return wgpuSurfacePresent(handle());
}

} // namespace webgpu
