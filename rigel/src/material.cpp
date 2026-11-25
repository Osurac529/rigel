#include "rigel/graphics/material.hpp"

namespace rigel::graphics {

Material::Material(
    const webgpu::Device &device,
    const webgpu::BindGroupLayout &bind_group_layout,
    const webgpu::TextureView &albedo,
    const webgpu::TextureView &normal,
    const webgpu::TextureView &roughness_metallic)
    : bind_group_(
          webgpu::BindGroupBuilder()
              .AddBinding(webgpu::BindingBuilder().SetBinding(0).SetTextureView(albedo).Build())
              .AddBinding(webgpu::BindingBuilder().SetBinding(1).SetTextureView(normal).Build())
              .AddBinding(
                  webgpu::BindingBuilder().SetBinding(2).SetTextureView(roughness_metallic).Build())
              .AddBinding(
                  webgpu::BindingBuilder()
                      .SetBinding(3)
                      .SetSampler(webgpu::SamplerBuilder().Build(device))
                      .Build())
              .SetLayout(bind_group_layout)
              .Build(device)) {}

const webgpu::BindGroup &Material::bind_group() const {
  return bind_group_;
}

} // namespace rigel::graphics
