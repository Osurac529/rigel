#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

namespace webgpu {

class Device;
class Sampler;

class SamplerBuilder {
public:
  SamplerBuilder();

  SamplerBuilder &SetAddressModeU(WGPUAddressMode address_mode_u);

  SamplerBuilder &SetAddressModeV(WGPUAddressMode address_mode_v);

  SamplerBuilder &SetAddressModeW(WGPUAddressMode address_mode_w);

  SamplerBuilder &SetMagFilter(WGPUFilterMode mag_filter);

  SamplerBuilder &SetMinFilter(WGPUFilterMode min_filter);

  SamplerBuilder &SetMipmapFilter(WGPUMipmapFilterMode mipmap_filter);

  SamplerBuilder &SetLodMinClamp(float lod_min_clamp);

  SamplerBuilder &SetLodMaxClamp(float lod_max_clamp);

  SamplerBuilder &SetCompare(WGPUCompareFunction compare);

  SamplerBuilder &SetMaxAnisotropy(std::uint16_t max_anisotropy);

  Sampler Build(Device &device);

private:
  WGPUSamplerDescriptor descriptor_ = WGPU_SAMPLER_DESCRIPTOR_INIT;
};

} // namespace webgpu
