#include "graphics/texture.hpp"

namespace rigel::graphics {

WGPUTextureFormat Texture::GetFormat() const {
  return wgpuTextureGetFormat(native());
}

} // namespace rigel::graphics
