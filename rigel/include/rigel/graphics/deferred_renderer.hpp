#pragma once

#include <vector>

#include "../generated/deferred_shaderper_frame_uniforms.hpp"
#include "rigel/graphics/render_targets.hpp"
#include "rigel/math/math.hpp"

namespace rigel::graphics {

class DeferredRenderer {
public:
  explicit DeferredRenderer(
      const webgpu::Device &device,
      const std::vector<webgpu::VertexBufferLayout> &vertex_buffer_layouts,
      std::uint32_t width,
      std::uint32_t height);

  void Resize(const webgpu::Device &device, std::uint32_t width, std::uint32_t height);

  webgpu::RenderPassEncoder CreateRenderPassEncoder(const webgpu::CommandEncoder &command_encoder);

  void SetWorldToCamera(webgpu::Queue &queue, const math::mat4x4f &world_to_camera);

  void SetCameraToProjection(webgpu::Queue &queue, const math::mat4x4f &camera_to_projection);

  const webgpu::BindGroupLayout &material_bind_group_layout() const;

  const webgpu::BindGroupLayout &per_draw_bind_group_layout() const;

  // todo: remove this when lighting pass is added
  const webgpu::TextureView &GetAlbedoView() const;

private:
  void UpdateRenderPassEncoderBuilder();

  generated::per_frame_uniforms per_frame_uniforms_;
  RenderTargets render_targets_;
  webgpu::BindGroupLayout material_bind_group_layout_;
  webgpu::BindGroupLayout per_draw_bind_group_layout_;
  webgpu::RenderPipeline render_pipeline_;
  webgpu::BindGroup per_frame_bind_group_;
  webgpu::RenderPassEncoderBuilder render_pass_encoder_builder_;
};

} // namespace rigel::graphics
