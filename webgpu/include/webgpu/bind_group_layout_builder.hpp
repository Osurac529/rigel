#pragma once

#include <vector>

#include <webgpu/wgpu.h>

namespace webgpu {

class BindGroupLayout;
class Device;

class BindGroupLayoutBuilder {
public:
  BindGroupLayoutBuilder &AddLayoutEntry(const WGPUBindGroupLayoutEntry &entry);

  BindGroupLayout Build(Device &device);

private:
  std::vector<WGPUBindGroupLayoutEntry> entries_;
  WGPUBindGroupLayoutDescriptor descriptor_ = WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT;
};

} // namespace webgpu
