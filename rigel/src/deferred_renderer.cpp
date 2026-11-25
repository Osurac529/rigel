#include "rigel/graphics/deferred_renderer.hpp"

#include "../generated/deferred_shaderper_draw_uniforms.hpp"
#include "rigel/graphics/color_render_target.hpp"

namespace rigel::graphics {

DeferredRenderer::DeferredRenderer(
    const webgpu::Device &device,
    const std::vector<webgpu::VertexBufferLayout> &vertex_buffer_layouts,
    const std::uint32_t width,
    const std::uint32_t height)
    : per_frame_uniforms_(device) {
  // world position (16 bytes)
  render_targets_.AddColorTarget(
      ColorRenderTarget(device, WGPUTextureFormat_RGBA32Float, width, height));
  // world normal (4 bytes)
  render_targets_.AddColorTarget(
      ColorRenderTarget(device, WGPUTextureFormat_RGB10A2Unorm, width, height));
  // albedo (4 bytes)
  render_targets_.AddColorTarget(
      ColorRenderTarget(device, WGPUTextureFormat_RGBA8Unorm, width, height));
  // roughness, metallic (4 bytes)
  render_targets_.AddColorTarget(
      ColorRenderTarget(device, WGPUTextureFormat_RG16Float, width, height));
  // depth
  render_targets_.SetDepthStencilTarget(
      graphics::DepthStencilRenderTarget(device, WGPUTextureFormat_Depth24Plus, width, height)
          .SetDepthClearValue(1.0f));

  // todo: create shader
  // todo: create bind group layouts
  const auto per_frame_bind_group_layout =
      webgpu::BindGroupLayoutBuilder()
          .AddLayoutEntry(
              webgpu::BindGroupLayoutEntryBuilder()
                  .SetBinding(0)
                  .SetVisibility(WGPUShaderStage_Vertex)
                  .SetBufferBindingLayout(
                      WGPUBufferBindingType_Uniform, per_frame_uniforms_.buffer().GetSize())
                  .Build())
          .Build(device);

  per_frame_bind_group_ = webgpu::BindGroupBuilder()
                              .AddBinding(
                                  webgpu::BindingBuilder()
                                      .SetBinding(0)
                                      .SetBuffer(per_frame_uniforms_.buffer())
                                      .Build())
                              .SetLayout(per_frame_bind_group_layout)
                              .Build(device);

  material_bind_group_layout_ =
      webgpu::BindGroupLayoutBuilder()
          .AddLayoutEntry(
              webgpu::BindGroupLayoutEntryBuilder()
                  .SetBinding(0)
                  .SetVisibility(WGPUShaderStage_Fragment)
                  .SetTextureBindingLayout(WGPUTextureSampleType_Float)
                  .Build())
          .AddLayoutEntry(
              webgpu::BindGroupLayoutEntryBuilder()
                  .SetBinding(1)
                  .SetVisibility(WGPUShaderStage_Fragment)
                  .SetTextureBindingLayout(WGPUTextureSampleType_Float)
                  .Build())
          .AddLayoutEntry(
              webgpu::BindGroupLayoutEntryBuilder()
                  .SetBinding(2)
                  .SetVisibility(WGPUShaderStage_Fragment)
                  .SetTextureBindingLayout(WGPUTextureSampleType_Float)
                  .Build())
          .AddLayoutEntry(
              webgpu::BindGroupLayoutEntryBuilder()
                  .SetBinding(3)
                  .SetVisibility(WGPUShaderStage_Fragment)
                  .SetSamplerBindingLayout(WGPUSamplerBindingType_Filtering)
                  .Build())
          .Build(device);

  per_draw_bind_group_layout_ =
      webgpu::BindGroupLayoutBuilder()
          .AddLayoutEntry(
              webgpu::BindGroupLayoutEntryBuilder()
                  .SetBinding(0)
                  .SetVisibility(WGPUShaderStage_Vertex)
                  .SetBufferBindingLayout(
                      WGPUBufferBindingType_Uniform,
                      // todo: could add a static method for getting size
                      generated::per_draw_uniforms(device).buffer().GetSize())
                  .Build())
          .Build(device);

  // create pipeline
  webgpu::FragmentStateBuilder fragment_state_builder;

  for (auto &color_target : render_targets_.color_targets()) {
    fragment_state_builder.AddColorTarget(color_target.state());
  }

  webgpu::VertexStateBuilder vertex_state_builder;

  for (const auto &vertex_buffer_layout : vertex_buffer_layouts) {
    vertex_state_builder.AddVertexBufferLayout(vertex_buffer_layout);
  }

  const webgpu::ShaderModule shader(device, std::filesystem::path("shaders/deferred_shader.wgsl"));

  render_pipeline_ =
      webgpu::RenderPipelineBuilder()
          .SetFrontFace(WGPUFrontFace_CW)
          .SetCullMode(WGPUCullMode_Back)
          .SetLayout(
              webgpu::PipelineLayoutBuilder()
                  .AddBindGroupLayout(per_frame_bind_group_layout)
                  .AddBindGroupLayout(material_bind_group_layout_)
                  .AddBindGroupLayout(per_draw_bind_group_layout_)
                  .Build(device))
          .SetDepthStencilState(render_targets_.GetDepthStencilTarget().state())
          .SetFragmentState(fragment_state_builder.SetShader(shader, "fs_main").Build())
          .SetVertexState(vertex_state_builder.SetShader(shader, "vs_main").Build())
          .Build(device);

  UpdateRenderPassEncoderBuilder();
}

void DeferredRenderer::Resize(
    const webgpu::Device &device,
    const std::uint32_t width,
    const std::uint32_t height) {
  render_targets_.Resize(device, width, height);

  UpdateRenderPassEncoderBuilder();
}

void DeferredRenderer::UpdateRenderPassEncoderBuilder() {
  render_pass_encoder_builder_.SetDepthStencilAttachment(
      render_targets_.GetDepthStencilTarget().attachment());

  auto &render_targets = render_targets_.color_targets();
  const auto size = static_cast<std::uint32_t>(render_targets.size());

  for (std::uint32_t i = 0; i < size; ++i) {
    render_pass_encoder_builder_.SetRenderPassColorAttachment(i, render_targets[i].attachment());
  }
}

webgpu::RenderPassEncoder
DeferredRenderer::CreateRenderPassEncoder(const webgpu::CommandEncoder &command_encoder) {
  auto render_pass_encoder = render_pass_encoder_builder_.Build(command_encoder);
  render_pass_encoder.SetPipeline(render_pipeline_);
  render_pass_encoder.SetBindGroup(0, per_frame_bind_group_);

  return render_pass_encoder;
}

void DeferredRenderer::SetWorldToCamera(
    webgpu::Queue &queue,
    const math::mat4x4f &world_to_camera) {
  per_frame_uniforms_.world_to_camera(queue, world_to_camera);
}

void DeferredRenderer::SetCameraToProjection(
    webgpu::Queue &queue,
    const math::mat4x4f &camera_to_projection) {
  per_frame_uniforms_.camera_to_projection(queue, camera_to_projection);
}

const webgpu::BindGroupLayout &DeferredRenderer::material_bind_group_layout() const {
  return material_bind_group_layout_;
}

const webgpu::BindGroupLayout &DeferredRenderer::per_draw_bind_group_layout() const {
  return per_draw_bind_group_layout_;
}

} // namespace rigel::graphics
