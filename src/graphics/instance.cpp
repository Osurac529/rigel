#include "graphics/instance.hpp"

#include "graphics/surface.hpp"
#include "graphics/window.hpp"

namespace rigel::graphics {

Instance::Instance(const WGPUInstanceDescriptor &descriptor)
    : WGPUObject(wgpuCreateInstance(&descriptor)) {}

std::vector<Adapter>
Instance::EnumerateAdapters(WGPUInstanceEnumerateAdapterOptions options) const {
  const auto num_adapters = wgpuInstanceEnumerateAdapters(native(), &options, nullptr);

  std::vector<WGPUAdapter> wgpu_adapters(num_adapters);

  wgpuInstanceEnumerateAdapters(native(), &options, wgpu_adapters.data());

  return {wgpu_adapters.begin(), wgpu_adapters.end()};
}

Surface Instance::CreateSurface(const Window &window) {
  WGPUSurfaceSourceWindowsHWND source = WGPU_SURFACE_SOURCE_WINDOWS_HWND_INIT;

  source.chain.sType = WGPUSType_SurfaceSourceWindowsHWND;
  source.hinstance = window.GetApplicationInstance();
  source.hwnd = window.GetHandle();

  WGPUSurfaceDescriptor surface_descriptor = WGPU_SURFACE_DESCRIPTOR_INIT;
  surface_descriptor.nextInChain = &source.chain;
  surface_descriptor.label = {"MyWin32Surface", WGPU_STRLEN};

  return Surface(wgpuInstanceCreateSurface(native(), &surface_descriptor));
}

} // namespace rigel::graphics
