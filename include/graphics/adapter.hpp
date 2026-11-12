#pragma once

#include <vector>

#include <webgpu/wgpu.h>

namespace rigel::graphics {

class AdapterInfo;
class Device;

class Adapter {
public:
  explicit Adapter(WGPUAdapter adapter);

  Adapter(const Adapter &);
  Adapter &operator=(const Adapter &);

  Adapter(Adapter &&) = default;
  Adapter &operator=(Adapter &&) = default;

  ~Adapter();

  Device RequestDevice(const WGPUDeviceDescriptor &descriptor = WGPU_DEVICE_DESCRIPTOR_INIT) const;

  AdapterInfo GetInfo() const;

  WGPULimits GetLimits() const;

  std::vector<WGPUFeatureName> GetFeatures() const;

  const WGPUAdapter &native() const;

private:
  WGPUAdapter adapter_;
};

} // namespace rigel::graphics
