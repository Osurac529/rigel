#pragma once

#include <filesystem>

#include "webgpu/webgpu.hpp"

namespace rigel::graphics {

class Material;

class MaterialBuilder {
public:
  MaterialBuilder &SetAlbedo(const std::filesystem::path &path);

  MaterialBuilder &SetNormal(const std::filesystem::path &path);

  MaterialBuilder &SetRoughnessMetallic(const std::filesystem::path &path);

  MaterialBuilder &SetBindGroupLayout(const webgpu::BindGroupLayout &bind_group_layout);

  Material Build(const webgpu::Device &device);

private:
  webgpu::TextureView albedo_;
  webgpu::TextureView normal_;
  webgpu::TextureView roughness_metallic_;
  webgpu::BindGroupLayout bind_group_layout_;
};

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

} // namespace rigel::graphics
