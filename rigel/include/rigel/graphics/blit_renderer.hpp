#pragma once

#include "webgpu/webgpu.hpp"

namespace rigel::graphics {

class BlitRenderer {
public:
  explicit BlitRenderer(const webgpu::Device &device, WGPUTextureFormat destination_format);

  void Blit(
      const webgpu::TextureView &destination,
      const webgpu::TextureView &source,
      const webgpu::Device &device,
      const webgpu::CommandEncoder &command_encoder);

private:
  webgpu::Sampler sampler_;
  webgpu::BindGroupLayout bind_group_layout_;
  webgpu::RenderPipeline render_pipeline_;
};

} // namespace rigel::graphics
