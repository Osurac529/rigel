#include "graphics/texture_view.hpp"

#include "graphics/texture.hpp"

namespace rigel::graphics {

TextureView::TextureView(Texture &texture, const WGPUTextureViewDescriptor &texture_view_descriptor)
    : TextureView(wgpuTextureCreateView(texture.native(), &texture_view_descriptor)) {}

} // namespace rigel::graphics
