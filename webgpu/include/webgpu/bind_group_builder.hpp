#pragma once

#include <vector>

#include <webgpu/wgpu.h>

#include "webgpu/bind_group_layout.hpp"
#include "webgpu/binding_builder.hpp"

namespace webgpu {

class BindGroup;
class Device;

class BindGroupBuilder {
public:
  BindGroupBuilder &AddBinding(const Binding &binding);

  BindGroupBuilder &SetLayout(const BindGroupLayout &layout);

  BindGroup Build(Device &device);

private:
  std::vector<Binding> bindings_;
  BindGroupLayout layout_;
  WGPUBindGroupDescriptor descriptor_ = WGPU_BIND_GROUP_DESCRIPTOR_INIT;
};

} // namespace webgpu
