#include "rigel/graphics/texture2d.hpp"

namespace rigel::graphics {

Texture2D::Texture2D(const webgpu::Texture &texture) : texture_(texture) {}

webgpu::TextureView Texture2D::View() const {
  return webgpu::TextureViewBuilder().SetUsage(WGPUTextureUsage_TextureBinding).Build(texture_);
}

const webgpu::Texture &Texture2D::texture() const {
  return texture_;
}

} // namespace rigel::graphics
