#include "graphics/buffer.hpp"

#include "graphics/device.hpp"
#include "graphics/queue.hpp"

namespace rigel::graphics {

namespace {

WGPUBufferDescriptor
CreateDescriptor(const WGPUBufferUsage usage, const std::vector<std::uint16_t> &indices) {
  // A writeBuffer operation must copy a number of bytes that is a multiple of 4.
  auto size = indices.size();

  if (indices.size() & 1) {
    ++size;
  }

  WGPUBufferDescriptor descriptor = WGPU_BUFFER_DESCRIPTOR_INIT;
  descriptor.usage = WGPUBufferUsage_Index | usage;
  descriptor.size = size * sizeof(std::uint16_t);

  return descriptor;
}

WGPUBufferDescriptor
CreateDescriptor(const WGPUBufferUsage usage, const std::vector<std::uint32_t> &indices) {
  WGPUBufferDescriptor descriptor = WGPU_BUFFER_DESCRIPTOR_INIT;
  descriptor.usage = WGPUBufferUsage_Index | usage;
  descriptor.size = indices.size() * sizeof(std::uint32_t);

  return descriptor;
}

} // namespace

Buffer::Buffer(Device &device, const WGPUBufferDescriptor &descriptor)
    : Buffer(wgpuDeviceCreateBuffer(device.native(), &descriptor)) {}

uint64_t Buffer::GetSize() const {
  return wgpuBufferGetSize(native());
}

IndexBuffer::IndexBuffer(Device &device, const std::vector<std::uint16_t> &indices)
    : Buffer(device, CreateDescriptor(WGPUBufferUsage_CopyDst, indices)),
      format_(WGPUIndexFormat_Uint16) {}

IndexBuffer::IndexBuffer(Device &device, Queue &queue, const std::vector<std::uint16_t> &indices)
    : IndexBuffer(device, indices) {
  queue.WriteBuffer(*this, indices.data());
}

IndexBuffer::IndexBuffer(Device &device, const std::vector<std::uint32_t> &indices)
    : Buffer(device, CreateDescriptor(WGPUBufferUsage_CopyDst, indices)),
      format_(WGPUIndexFormat_Uint32) {}

IndexBuffer::IndexBuffer(Device &device, Queue &queue, const std::vector<std::uint32_t> &indices)
    : IndexBuffer(device, indices) {
  queue.WriteBuffer(*this, indices.data());
}

WGPUIndexFormat IndexBuffer::format() const {
  return format_;
}

} // namespace rigel::graphics
