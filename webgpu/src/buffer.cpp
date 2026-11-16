#include "webgpu/buffer.hpp"

#include "webgpu/device.hpp"

namespace webgpu {

namespace {

WGPUBuffer Create(
    Device &device,
    const WGPUBufferUsage usage,
    std::uint64_t size,
    const WGPUBool mapped_at_creation) {
  WGPUBufferDescriptor descriptor = WGPU_BUFFER_DESCRIPTOR_INIT;
  descriptor.usage = usage;

  // todo: revisit this, it may cause problems like address sanitizer read out of bounds errors
  // size must be multiple of 4
  if (const auto remainder = size % 4; remainder > 0) {
    size += remainder;
  }

  descriptor.size = size;
  descriptor.mappedAtCreation = mapped_at_creation;

  return wgpuDeviceCreateBuffer(device.handle(), &descriptor);
}

} // namespace

Buffer::Buffer(
    Device &device,
    const WGPUBufferUsage usage,
    const std::uint64_t size,
    const WGPUBool mapped_at_creation)
    : Buffer(Create(device, usage, size, mapped_at_creation)) {}

uint64_t Buffer::GetSize() const {
  return wgpuBufferGetSize(handle());
}

} // namespace webgpu
