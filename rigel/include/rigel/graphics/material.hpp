#pragma once

#include <filesystem>

#include "webgpu/webgpu.hpp"
#include "rigel/image/image2d.hpp"

namespace rigel::graphics {

class Material {
public:
  explicit Material(
      const webgpu::Device &device,
      const webgpu::BindGroupLayout &bind_group_layout,
      const webgpu::TextureView &albedo,
      const webgpu::TextureView &normal,
      const webgpu::TextureView &roughness_metallic);

  const webgpu::BindGroup &bind_group() const;

private:
  webgpu::BindGroup bind_group_;
};

class MaterialBuilder {
public:
  MaterialBuilder &SetAlbedo(image::Image2DRGBA8 &&albedo);

  MaterialBuilder &SetNormal(image::Image2DRGBA8 &&normal);

  MaterialBuilder &SetRoughnessMetallic(image::Image2DRG8 &&roughness_metallic);

  MaterialBuilder &SetBindGroupLayout(const webgpu::BindGroupLayout &bind_group_layout);

  Material Build(const webgpu::Device &device) const;

private:
  image::Image2DRGBA8 albedo_;
  image::Image2DRGBA8 normal_;
  image::Image2DRG8 roughness_metallic_;
  webgpu::BindGroupLayout bind_group_layout_;
};


} // namespace rigel::graphics
