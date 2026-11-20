#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class Texture : public Object<WGPUTexture, wgpuTextureAddRef, wgpuTextureRelease> {
public:
  using Object::Object;

  WGPUTextureFormat GetFormat() const;

  std::uint32_t GetDepthOrArrayLayers() const;

  WGPUTextureDimension GetDimension() const;

  std::uint32_t GetHeight() const;

  std::uint32_t GetMipLevelCount() const;

  std::uint32_t GetSampleCount() const;

  WGPUTextureViewDimension TextureBindingViewDimension() const;

  WGPUTextureUsage GetUsage() const;
};

} // namespace webgpu
