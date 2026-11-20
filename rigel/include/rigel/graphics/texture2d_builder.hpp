#pragma once

#include "rigel/image/image2d_fwd.hpp"
#include "webgpu/webgpu.hpp"

namespace rigel::graphics {

class Texture2D;

class Texture2DBuilder {
public:
  Texture2DBuilder &SetUsage(WGPUTextureUsage value);

  Texture2DBuilder &SetMipLevelCount(std::uint32_t value);

  Texture2DBuilder &SetSampleCount(std::uint32_t value);

  Texture2D Build(webgpu::Device &device, const image::Image2DRGB8 &image);

  Texture2D Build(webgpu::Device &device, const image::Image2DRGBA8 &image);

private:
  WGPUTextureUsage usage_ = WGPUTextureUsage_None;
  webgpu::TextureBuilder builder_;
};

} // namespace rigel::graphics
