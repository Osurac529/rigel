#include "webgpu/texture_builder.hpp"

#include "webgpu/device.hpp"
#include "webgpu/texture.hpp"

namespace webgpu {

TextureBuilder &TextureBuilder::AddViewFormat(const WGPUTextureFormat value) {
  view_formats_.push_back(value);

  return *this;
}

TextureBuilder &TextureBuilder::SetUsage(const WGPUTextureUsage value) {
  descriptor_.usage = value;

  return *this;
}

TextureBuilder &TextureBuilder::SetDimension(const WGPUTextureDimension value) {
  descriptor_.dimension = value;

  return *this;
}

TextureBuilder &TextureBuilder::SetSize(const WGPUExtent3D value) {
  descriptor_.size = value;

  return *this;
}

TextureBuilder &TextureBuilder::SetFormat(const WGPUTextureFormat value) {
  descriptor_.format = value;

  return *this;
}

TextureBuilder &TextureBuilder::SetMipLevelCount(const std::uint32_t value) {
  descriptor_.mipLevelCount = value;

  return *this;
}

TextureBuilder &TextureBuilder::SetSampleCount(const std::uint32_t value) {
  descriptor_.sampleCount = value;

  return *this;
}

Texture TextureBuilder::Build(Device &device) {
  descriptor_.viewFormatCount = view_formats_.size();
  descriptor_.viewFormats = view_formats_.data();

  return Texture(wgpuDeviceCreateTexture(device.handle(), &descriptor_));
}

} // namespace webgpu