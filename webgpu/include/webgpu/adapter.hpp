#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class AdapterInfo;

class Adapter : public Object<WGPUAdapter, wgpuAdapterAddRef, wgpuAdapterRelease> {
public:
  using Object::Object;

  AdapterInfo GetInfo() const;

  WGPULimits GetLimits() const;

  std::vector<WGPUFeatureName> GetFeatures() const;
};

} // namespace webgpu
