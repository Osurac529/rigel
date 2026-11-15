#include "graphics/buffer.hpp"

#include "graphics/device.hpp"

namespace rigel::graphics {

Buffer::Buffer(Device &device, const WGPUBufferDescriptor &descriptor)
    : Buffer(wgpuDeviceCreateBuffer(device.native(), &descriptor)) {}

uint64_t Buffer::GetSize() const {
  return wgpuBufferGetSize(native());
}

} // namespace rigel::graphics
