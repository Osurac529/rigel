#include "webgpu/texture.hpp"

namespace webgpu {

WGPUTextureFormat Texture::GetFormat() const {
  return wgpuTextureGetFormat(handle());
}

} // namespace rigel::graphics
