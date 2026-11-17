#pragma once

#include <cstdint>
#include <vector>

#include <webgpu/wgpu.h>

namespace webgpu {

class BindGroupLayout;

class BindGroupLayoutEntryBuilder {
public:
  BindGroupLayoutEntryBuilder &SetBinding(std::uint32_t value);

  BindGroupLayoutEntryBuilder &SetVisibility(WGPUShaderStage visibility);

  BindGroupLayoutEntryBuilder &SetBindingArraySize(std::uint32_t value);

  BindGroupLayoutEntryBuilder &SetBufferBindingLayout(
      WGPUBufferBindingType type,
      std::uint64_t min_binding_size,
      WGPUBool has_dynamic_offset = WGPU_FALSE);

  BindGroupLayoutEntryBuilder &SetSamplerBindingLayout(WGPUSamplerBindingType type);

  BindGroupLayoutEntryBuilder &SetTextureBindingLayout(
      WGPUTextureSampleType sample_type,
      WGPUTextureViewDimension view_dimension = WGPUTextureViewDimension_2D,
      WGPUBool multisampled = WGPU_FALSE);

  BindGroupLayoutEntryBuilder &SetStorageBindingLayout(
      WGPUTextureFormat format,
      WGPUStorageTextureAccess access = WGPUStorageTextureAccess_WriteOnly,
      WGPUTextureViewDimension view_dimension = WGPUTextureViewDimension_2D);

  const WGPUBindGroupLayoutEntry &Build() const;

private:
  WGPUBindGroupLayoutEntry entry_ = WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT;
};

} // namespace webgpu
