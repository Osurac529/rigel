#include "webgpu/bind_group_layout_entry_builder.hpp"

namespace webgpu {

BindGroupLayoutEntryBuilder &BindGroupLayoutEntryBuilder::SetBinding(const std::uint32_t value) {
  entry_.binding = value;

  return *this;
}

BindGroupLayoutEntryBuilder &
BindGroupLayoutEntryBuilder::SetVisibility(const WGPUShaderStage visibility) {
  entry_.visibility = visibility;

  return *this;
}

BindGroupLayoutEntryBuilder &
BindGroupLayoutEntryBuilder::SetBindingArraySize(const std::uint32_t value) {
  entry_.bindingArraySize = value;

  return *this;
}

BindGroupLayoutEntryBuilder &BindGroupLayoutEntryBuilder::SetBufferBindingLayout(
    const WGPUBufferBindingType type,
    const std::uint64_t min_binding_size,
    const WGPUBool has_dynamic_offset) {
  entry_.buffer.type = type;
  entry_.buffer.minBindingSize = min_binding_size;
  entry_.buffer.hasDynamicOffset = has_dynamic_offset;

  return *this;
}

BindGroupLayoutEntryBuilder &
BindGroupLayoutEntryBuilder::SetSamplerBindingLayout(const WGPUSamplerBindingType type) {
  entry_.sampler.type = type;

  return *this;
}

BindGroupLayoutEntryBuilder &BindGroupLayoutEntryBuilder::SetTextureBindingLayout(
    const WGPUTextureSampleType sample_type,
    const WGPUTextureViewDimension view_dimension,
    const WGPUBool multisampled) {
  entry_.texture.sampleType = sample_type;
  entry_.texture.viewDimension = view_dimension;
  entry_.texture.multisampled = multisampled;

  return *this;
}

BindGroupLayoutEntryBuilder &BindGroupLayoutEntryBuilder::SetStorageBindingLayout(
    const WGPUTextureFormat format,
    const WGPUStorageTextureAccess access,
    const WGPUTextureViewDimension view_dimension) {
  entry_.storageTexture.format = format;
  entry_.storageTexture.access = access;
  entry_.storageTexture.viewDimension = view_dimension;

  return *this;
}

const WGPUBindGroupLayoutEntry &BindGroupLayoutEntryBuilder::Build() const {
  return entry_;
}

} // namespace webgpu
