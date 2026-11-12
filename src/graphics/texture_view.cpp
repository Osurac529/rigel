#include "graphics/texture_view.hpp"

namespace rigel::graphics {

TextureView::TextureView(
    WGPUTexture texture,
    const WGPUTextureViewDescriptor &texture_view_descriptor)
    : WGPUObject(wgpuTextureCreateView(texture, &texture_view_descriptor)) {}

} // namespace rigel::graphics
