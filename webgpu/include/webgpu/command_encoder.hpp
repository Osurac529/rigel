#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class CommandBuffer;
class Device;

class CommandEncoder
    : public Object<WGPUCommandEncoder, wgpuCommandEncoderAddRef, wgpuCommandEncoderRelease> {
public:
  using Object::Object;

  explicit CommandEncoder(
      Device &device,
      const WGPUCommandEncoderDescriptor &descriptor = WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT);

  CommandBuffer
  Finish(const WGPUCommandBufferDescriptor &descriptor = WGPU_COMMAND_BUFFER_DESCRIPTOR_INIT) const;
};

} // namespace webgpu
