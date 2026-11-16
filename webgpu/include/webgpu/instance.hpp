#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/adapter.hpp"
#include "webgpu/object.hpp"

namespace webgpu {

class Instance : public Object<WGPUInstance, wgpuInstanceAddRef, wgpuInstanceRelease> {
public:
  using Object::Object;

  std::vector<Adapter> EnumerateAdapters(
      const WGPUInstanceEnumerateAdapterOptions &options = {
          .nextInChain = nullptr,
          .backends = WGPUInstanceBackend_All,
      }) const;
};

} // namespace webgpu
