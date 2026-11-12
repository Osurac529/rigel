#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class AdapterInfo;
class Device;

class Adapter : public WGPUObject<WGPUAdapter, wgpuAdapterAddRef, wgpuAdapterRelease> {
public:
  using WGPUObject::WGPUObject;

  Device RequestDevice(const WGPUDeviceDescriptor &descriptor = WGPU_DEVICE_DESCRIPTOR_INIT) const;

  AdapterInfo GetInfo() const;

  WGPULimits GetLimits() const;

  std::vector<WGPUFeatureName> GetFeatures() const;
};

} // namespace rigel::graphics
