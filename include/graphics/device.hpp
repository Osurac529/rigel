#pragma once

#include <vector>

#include <webgpu/wgpu.h>

namespace rigel::graphics {

class Queue;
class CommandEncoder;

class Device {
public:
  explicit Device(WGPUDevice device);

  Device(const Device &);
  Device &operator=(const Device &);

  Device(Device &&) = default;
  Device &operator=(Device &&) = default;

  ~Device();

  WGPULimits GetLimits() const;

  std::vector<WGPUFeatureName> GetFeatures() const;

  Queue GetQueue() const;

  CommandEncoder CreateCommandEncoder(
      const WGPUCommandEncoderDescriptor &encoder_description =
          WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT);

  const WGPUDevice &native() const;

private:
  WGPUDevice device_;
};

} // namespace rigel::graphics
