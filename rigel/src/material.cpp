#include "rigel/graphics/material.hpp"

#include "rigel/graphics/texture2d.hpp"
#include "rigel/graphics/texture2d_builder.hpp"

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

MaterialBuilder &MaterialBuilder::SetAlbedo(image::Image2DRGBA8 &&albedo) {
  albedo_ = std::move(albedo);

  return *this;
}

MaterialBuilder &MaterialBuilder::SetNormal(image::Image2DRGBA8 &&normal) {
  normal_ = std::move(normal);

  return *this;
}

MaterialBuilder &MaterialBuilder::SetRoughnessMetallic(image::Image2DRG8 &&roughness_metallic) {
  roughness_metallic_ = std::move(roughness_metallic);

  return *this;
}

MaterialBuilder &
MaterialBuilder::SetBindGroupLayout(const webgpu::BindGroupLayout &bind_group_layout) {
  bind_group_layout_ = bind_group_layout;

  return *this;
}

Material MaterialBuilder::Build(const webgpu::Device &device) const {
  auto albedo_view =
      Texture2DBuilder().SetUsage(WGPUTextureUsage_TextureBinding).Build(device, albedo_).View();
  auto normal_view =
      Texture2DBuilder().SetUsage(WGPUTextureUsage_TextureBinding).Build(device, normal_).View();
  auto roughness_metallic_view = Texture2DBuilder()
                                     .SetUsage(WGPUTextureUsage_TextureBinding)
                                     .Build(device, roughness_metallic_)
                                     .View();

  return Material(device, bind_group_layout_, albedo_view, normal_view, roughness_metallic_view);
}

} // namespace rigel::graphics
