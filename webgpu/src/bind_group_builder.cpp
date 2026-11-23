#include "webgpu/bind_group_builder.hpp"

#include "webgpu/bind_group.hpp"
#include "webgpu/device.hpp"

namespace webgpu {

BindGroupBuilder &BindGroupBuilder::AddBinding(const Binding &binding) {
  bindings_.push_back(binding);

  return *this;
}

BindGroupBuilder &BindGroupBuilder::SetLayout(const BindGroupLayout &layout) {
  layout_ = layout;

  return *this;
}

BindGroup BindGroupBuilder::Build(const Device &device) {
  std::vector<WGPUBindGroupEntry> wgpu_bindings;
  wgpu_bindings.reserve(bindings_.size());

  for (auto &binding : bindings_) {
    wgpu_bindings.push_back(binding.Get());
  }

  descriptor_.entryCount = wgpu_bindings.size();
  descriptor_.entries = wgpu_bindings.data();
  descriptor_.layout = layout_.handle();

  return BindGroup(wgpuDeviceCreateBindGroup(device.handle(), &descriptor_));
}

} // namespace webgpu
