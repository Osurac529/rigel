#include "graphics/texture_view.hpp"

#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

TextureView::TextureView(
    WGPUTexture texture,
    const WGPUTextureViewDescriptor &texture_view_descriptor)
    : texture_view_(wgpuTextureCreateView(texture, &texture_view_descriptor)) {
  if (!texture_view_) {
    throw GraphicsException("Texture view creation failed.");
  }
}

TextureView::TextureView(const TextureView &other) : texture_view_(other.texture_view_) {
  wgpuTextureViewAddRef(texture_view_);
}

TextureView &TextureView::operator=(const TextureView &other) {
  if (this != &other) {
    texture_view_ = other.texture_view_;
    wgpuTextureViewAddRef(texture_view_);
  }

  return *this;
}

TextureView::~TextureView() {
  wgpuTextureViewRelease(texture_view_);
}

const WGPUTextureView &TextureView::native() const {
  return texture_view_;
}

} // namespace rigel::graphics
