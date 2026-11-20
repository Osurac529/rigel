#include "rigel/graphics/texture2d_builder.hpp"

#include "rigel/graphics/texture2d.hpp"
#include "rigel/image/convert.hpp"
#include "rigel/image/image2d.hpp"

namespace rigel::graphics {

Texture2DBuilder &Texture2DBuilder::SetUsage(const WGPUTextureUsage value) {
  usage_ = value;

  return *this;
}

Texture2DBuilder &Texture2DBuilder::SetMipLevelCount(const std::uint32_t value) {
  builder_.SetMipLevelCount(value);

  return *this;
}

Texture2DBuilder &Texture2DBuilder::SetSampleCount(const std::uint32_t value) {
  builder_.SetSampleCount(value);

  return *this;
}

Texture2D Texture2DBuilder::Build(webgpu::Device &device, const image::Image2DRGB8 &image) {
  // need to convert RGB to RGBA because there is no texture format for RGB
  return Build(device, image::Convert(image));
}

Texture2D Texture2DBuilder::Build(webgpu::Device &device, const image::Image2DRGBA8 &image) {
  const WGPUExtent3D size = {image.width(), image.height(), 1};

  Texture2D texture(builder_.SetDimension(WGPUTextureDimension_2D)
                        .SetFormat(WGPUTextureFormat_RGBA8Unorm)
                        .SetSize(size)
                        .SetUsage(usage_ | WGPUTextureUsage_CopyDst)
                        .Build(device));

  // todo: create each mip-map level by down sampling image
  WGPUTexelCopyTextureInfo destination = WGPU_TEXEL_COPY_TEXTURE_INFO_INIT;
  destination.texture = texture.texture().handle();
  destination.aspect = WGPUTextureAspect_All;

  WGPUTexelCopyBufferLayout layout = WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT;
  layout.bytesPerRow = image.BytesPerRow();
  layout.rowsPerImage = image.height();

  device.GetQueue().WriteTexture(destination, image.data(), image.BytesSize(), layout, size);

  return texture;
}

} // namespace rigel::graphics
