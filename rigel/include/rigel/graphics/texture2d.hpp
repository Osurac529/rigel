#pragma once

#include "webgpu/webgpu.hpp"

namespace rigel::graphics {

class Texture2D {
public:
  explicit Texture2D(const webgpu::Texture &texture);

  webgpu::TextureView View() const;

  const webgpu::Texture &texture() const;

private:
  mutable webgpu::Texture texture_;
};

} // namespace rigel::graphics
