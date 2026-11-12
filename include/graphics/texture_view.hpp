#pragma once

#include <webgpu/wgpu.h>

#include "utilities/move_only.hpp"

namespace rigel::graphics {

class TextureView {
public:
  explicit TextureView(
      WGPUTexture texture,
      const WGPUTextureViewDescriptor &texture_view_descriptor);

  TextureView(const TextureView &);
  TextureView &operator=(const TextureView &);

  TextureView(TextureView &&) = default;
  TextureView &operator=(TextureView &&) = default;

  ~TextureView();

  const WGPUTextureView &native() const;

private:
  WGPUTextureView texture_view_;
};

} // namespace rigel::graphics
