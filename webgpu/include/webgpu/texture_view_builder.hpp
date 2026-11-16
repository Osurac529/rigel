#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

namespace webgpu {

class TextureView;
class Texture;

class TextureViewBuilder {
public:
  TextureViewBuilder();

  TextureViewBuilder &SetFormat(WGPUTextureFormat format);

  TextureViewBuilder &SetDimension(WGPUTextureViewDimension dimension);

  TextureViewBuilder &SetBaseMipLevel(std::uint32_t value);

  TextureViewBuilder &SetMipLevelCount(std::uint32_t value);

  TextureViewBuilder &SetBaseArrayLayer(std::uint32_t value);

  TextureViewBuilder &SetArrayLayerCount(std::uint32_t value);

  TextureViewBuilder &SetAspect(WGPUTextureAspect aspect);

  TextureViewBuilder &SetUsage(WGPUTextureUsage usage);

  TextureView Build(Texture& texture);

private:
  WGPUTextureViewDescriptor descriptor_ = WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT;
};

} // namespace webgpu
