#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/adapter.hpp"
#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class Window;
class Surface;

class Instance : public WGPUObject<WGPUInstance, wgpuInstanceAddRef, wgpuInstanceRelease> {
public:
  using WGPUObject::WGPUObject;

  explicit Instance(const WGPUInstanceDescriptor &descriptor = WGPU_INSTANCE_DESCRIPTOR_INIT);

  std::vector<Adapter> EnumerateAdapters(
      WGPUInstanceEnumerateAdapterOptions options = {
          .nextInChain = nullptr,
          .backends = WGPUInstanceBackend_All,
      }) const;

  Surface CreateSurface(const Window &window);
};

} // namespace rigel::graphics
