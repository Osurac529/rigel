#include "webgpu/texture.hpp"

namespace webgpu {

WGPUTextureFormat Texture::GetFormat() const {
  return wgpuTextureGetFormat(handle());
}

std::uint32_t Texture::GetDepthOrArrayLayers() const {
  return wgpuTextureGetDepthOrArrayLayers(handle());
}

WGPUTextureDimension Texture::GetDimension() const {
  return wgpuTextureGetDimension(handle());
}

std::uint32_t Texture::GetWidth() const {
  return wgpuTextureGetWidth(handle());
}

std::uint32_t Texture::GetHeight() const {
  return wgpuTextureGetHeight(handle());
}

std::uint32_t Texture::GetMipLevelCount() const {
  return wgpuTextureGetMipLevelCount(handle());
}

std::uint32_t Texture::GetSampleCount() const {
  return wgpuTextureGetSampleCount(handle());
}

WGPUTextureViewDimension Texture::GetTextureBindingViewDimension() const {
  return wgpuTextureGetTextureBindingViewDimension(handle());
}

WGPUTextureUsage Texture::GetUsage() const {
  return wgpuTextureGetUsage(handle());
}

} // namespace webgpu
