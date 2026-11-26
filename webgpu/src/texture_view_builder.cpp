#include "webgpu/texture_view_builder.hpp"

#include "webgpu/texture.hpp"
#include "webgpu/texture_view.hpp"

namespace webgpu {

TextureViewBuilder::TextureViewBuilder() {
  descriptor_.dimension = WGPUTextureViewDimension_2D;
  descriptor_.baseMipLevel = 0;
  descriptor_.mipLevelCount = 1;
  descriptor_.baseArrayLayer = 0;
  descriptor_.arrayLayerCount = 1;
  descriptor_.aspect = WGPUTextureAspect_All;
}

TextureViewBuilder &TextureViewBuilder::SetFormat(const WGPUTextureFormat format) {
  descriptor_.format = format;

  return *this;
}

TextureViewBuilder &TextureViewBuilder::SetDimension(const WGPUTextureViewDimension dimension) {
  descriptor_.dimension = dimension;

  return *this;
}

TextureViewBuilder &TextureViewBuilder::SetBaseMipLevel(const std::uint32_t value) {
  descriptor_.baseMipLevel = value;

  return *this;
}

TextureViewBuilder &TextureViewBuilder::SetMipLevelCount(const std::uint32_t value) {
  descriptor_.mipLevelCount = value;

  return *this;
}

TextureViewBuilder &TextureViewBuilder::SetBaseArrayLayer(const std::uint32_t value) {
  descriptor_.baseArrayLayer = value;

  return *this;
}

TextureViewBuilder &TextureViewBuilder::SetArrayLayerCount(const std::uint32_t value) {
  descriptor_.arrayLayerCount = value;

  return *this;
}

TextureViewBuilder &TextureViewBuilder::SetAspect(const WGPUTextureAspect aspect) {
  descriptor_.aspect = aspect;

  return *this;
}

TextureViewBuilder &TextureViewBuilder::SetUsage(const WGPUTextureUsage usage) {
  descriptor_.usage = usage;

  return *this;
}

TextureView TextureViewBuilder::Build(const Texture &texture) {
  if (WGPUTextureFormat_Undefined == descriptor_.format) {
    descriptor_.format = texture.GetFormat();
  }

  if (WGPU_MIP_LEVEL_COUNT_UNDEFINED == descriptor_.mipLevelCount) {
    descriptor_.mipLevelCount = texture.GetMipLevelCount();
  }

  if (WGPUTextureViewDimension_Undefined == descriptor_.dimension) {
    switch (texture.GetDimension()) {
    case WGPUTextureDimension_1D:
      descriptor_.dimension = WGPUTextureViewDimension_1D;
      break;
    case WGPUTextureDimension_2D:
      descriptor_.dimension = WGPUTextureViewDimension_2D;
      break;
    case WGPUTextureDimension_3D:
      descriptor_.dimension = WGPUTextureViewDimension_3D;
      break;
    }
  }

  return TextureView(wgpuTextureCreateView(texture.handle(), &descriptor_));
}

} // namespace webgpu