#include "webgpu/bind_group_layout_builder.hpp"

#include "webgpu/bind_group_layout.hpp"
#include "webgpu/device.hpp"

namespace webgpu {

BindGroupLayoutBuilder &
BindGroupLayoutBuilder::AddLayoutEntry(const WGPUBindGroupLayoutEntry &entry) {
  entries_.push_back(entry);

  return *this;
}

BindGroupLayout BindGroupLayoutBuilder::Build(const Device &device) {
  descriptor_.entryCount = entries_.size();
  descriptor_.entries = entries_.data();

  return BindGroupLayout(wgpuDeviceCreateBindGroupLayout(device.handle(), &descriptor_));
}

} // namespace webgpu
