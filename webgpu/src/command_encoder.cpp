#include "webgpu/command_encoder.hpp"

#include "webgpu/command_buffer.hpp"
#include "webgpu/device.hpp"

namespace webgpu {

CommandEncoder::CommandEncoder(const Device &device, const WGPUCommandEncoderDescriptor &descriptor)
    : CommandEncoder(wgpuDeviceCreateCommandEncoder(device.handle(), &descriptor)) {}

CommandBuffer CommandEncoder::Finish(const WGPUCommandBufferDescriptor &descriptor) const {
  return CommandBuffer(wgpuCommandEncoderFinish(handle(), &descriptor));
}

} // namespace webgpu
