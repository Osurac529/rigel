#include "webgpu/sampler_builder.hpp"

#include "webgpu/device.hpp"
#include "webgpu/sampler.hpp"

namespace webgpu {

SamplerBuilder::SamplerBuilder() {
  descriptor_.addressModeU = WGPUAddressMode_ClampToEdge;
  descriptor_.addressModeV = WGPUAddressMode_ClampToEdge;
  descriptor_.addressModeW = WGPUAddressMode_ClampToEdge;
  descriptor_.minFilter = WGPUFilterMode_Linear;
  descriptor_.magFilter = WGPUFilterMode_Linear;
  descriptor_.mipmapFilter = WGPUMipmapFilterMode_Linear;
}

SamplerBuilder &SamplerBuilder::SetAddressModeU(const WGPUAddressMode address_mode_u) {
  descriptor_.addressModeU = address_mode_u;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetAddressModeV(const WGPUAddressMode address_mode_v) {
  descriptor_.addressModeV = address_mode_v;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetAddressModeW(const WGPUAddressMode address_mode_w) {
  descriptor_.addressModeW = address_mode_w;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetMagFilter(const WGPUFilterMode mag_filter) {
  descriptor_.magFilter = mag_filter;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetMinFilter(const WGPUFilterMode min_filter) {
  descriptor_.minFilter = min_filter;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetMipmapFilter(const WGPUMipmapFilterMode mipmap_filter) {
  descriptor_.mipmapFilter = mipmap_filter;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetLodMinClamp(const float lod_min_clamp) {
  descriptor_.lodMinClamp = lod_min_clamp;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetLodMaxClamp(const float lod_max_clamp) {
  descriptor_.lodMaxClamp = lod_max_clamp;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetCompare(const WGPUCompareFunction compare) {
  descriptor_.compare = compare;

  return *this;
}

SamplerBuilder &SamplerBuilder::SetMaxAnisotropy(const std::uint16_t max_anisotropy) {
  descriptor_.maxAnisotropy = max_anisotropy;

  return *this;
}

Sampler SamplerBuilder::Build(Device &device) {
  return Sampler(wgpuDeviceCreateSampler(device.handle(), &descriptor_));
}

} // namespace webgpu
