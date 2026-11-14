#include "graphics/texture_view.hpp"

#include "graphics/texture.hpp"

namespace rigel::graphics {

TextureView::TextureView(Texture &texture, const WGPUTextureViewDescriptor &descriptor)
    : TextureView(wgpuTextureCreateView(texture.native(), &descriptor)) {}

} // namespace rigel::graphics
