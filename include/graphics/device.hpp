#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class Queue;
class CommandEncoder;

class Device : public WGPUObject<WGPUDevice, wgpuDeviceAddRef, wgpuDeviceRelease> {
public:
  using WGPUObject::WGPUObject;

  WGPULimits GetLimits() const;

  std::vector<WGPUFeatureName> GetFeatures() const;

  Queue GetQueue() const;

  CommandEncoder CreateCommandEncoder(
      const WGPUCommandEncoderDescriptor &encoder_description =
          WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT);
};

} // namespace rigel::graphics
