#pragma once

#include <cstdint>
#include <vector>

#include <webgpu/wgpu.h>

namespace webgpu {

class BindGroupLayout;
class PipelineLayout;
class Device;

class PipelineLayoutBuilder {
public:
  PipelineLayoutBuilder &AddBindGroupLayout(const BindGroupLayout &bind_group_layout);

  PipelineLayoutBuilder &SetImmediateSize(std::uint32_t immediate_size);

  PipelineLayout Build(const Device &device);

private:
  std::vector<BindGroupLayout> bind_group_layouts_;
  WGPUPipelineLayoutDescriptor descriptor_ = WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT;
};

} // namespace webgpu
