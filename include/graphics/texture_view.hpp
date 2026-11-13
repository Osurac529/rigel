#pragma once

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class Texture;

class TextureView
    : public WGPUObject<WGPUTextureView, wgpuTextureViewAddRef, wgpuTextureViewRelease> {
public:
  using WGPUObject::WGPUObject;

  explicit TextureView(
      Texture& texture,
      const WGPUTextureViewDescriptor &texture_view_descriptor = WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT);
};

} // namespace rigel::graphics
