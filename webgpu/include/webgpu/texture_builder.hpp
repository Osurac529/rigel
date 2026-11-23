#pragma once

#include <cstdint>
#include <vector>

#include <webgpu/wgpu.h>

namespace webgpu {

class Texture;
class Device;

class TextureBuilder {
public:
  TextureBuilder &AddViewFormat(WGPUTextureFormat value);

  TextureBuilder &SetUsage(WGPUTextureUsage value);

  TextureBuilder &SetDimension(WGPUTextureDimension value);

  TextureBuilder &SetSize(WGPUExtent3D value);

  TextureBuilder &SetFormat(WGPUTextureFormat value);

  TextureBuilder &SetMipLevelCount(std::uint32_t value);

  TextureBuilder &SetSampleCount(std::uint32_t value);

  Texture Build(const Device &device);

private:
  std::vector<WGPUTextureFormat> view_formats_;
  WGPUTextureDescriptor descriptor_ = WGPU_TEXTURE_DESCRIPTOR_INIT;
};

} // namespace webgpu
