#include "webgpu/pipeline_layout_builder.hpp"

#include "webgpu/bind_group_layout.hpp"
#include "webgpu/device.hpp"
#include "webgpu/pipeline_layout.hpp"

namespace webgpu {

PipelineLayoutBuilder &
PipelineLayoutBuilder::AddBindGroupLayout(const BindGroupLayout &bind_group_layout) {
  bind_group_layouts_.push_back(bind_group_layout);

  return *this;
}

PipelineLayoutBuilder &PipelineLayoutBuilder::SetImmediateSize(std::uint32_t immediate_size) {
  descriptor_.immediateSize = immediate_size;

  return *this;
}

PipelineLayout PipelineLayoutBuilder::Build(const Device &device) {
  std::vector<WGPUBindGroupLayout> wgpu_bind_group_layouts;
  wgpu_bind_group_layouts.reserve(bind_group_layouts_.size());

  for (const auto &bind_group_layout : bind_group_layouts_) {
    wgpu_bind_group_layouts.push_back(bind_group_layout.handle());
  }

  descriptor_.bindGroupLayoutCount = wgpu_bind_group_layouts.size();
  descriptor_.bindGroupLayouts = wgpu_bind_group_layouts.data();

  return PipelineLayout(wgpuDeviceCreatePipelineLayout(device.handle(), &descriptor_));
}

} // namespace webgpu