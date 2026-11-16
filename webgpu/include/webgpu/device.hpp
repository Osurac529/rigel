#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class Queue;

class Device : public Object<WGPUDevice, wgpuDeviceAddRef, wgpuDeviceRelease> {
public:
  using Object::Object;

  WGPULimits GetLimits() const;

  std::vector<WGPUFeatureName> GetFeatures() const;

  Queue GetQueue() const;
};

} // namespace webgpu
