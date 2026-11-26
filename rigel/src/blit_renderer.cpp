#include "rigel/graphics/blit_renderer.hpp"

namespace rigel::graphics {

BlitRenderer::BlitRenderer(const webgpu::Device &device, const WGPUTextureFormat destination_format)
    : sampler_(
          webgpu::SamplerBuilder()
              .SetMagFilter(WGPUFilterMode_Nearest)
              .SetMinFilter(WGPUFilterMode_Nearest)
              .SetMipmapFilter(WGPUMipmapFilterMode_Nearest)
              .Build(device)),
      bind_group_layout_(
          webgpu::BindGroupLayoutBuilder()
              .AddLayoutEntry(
                  webgpu::BindGroupLayoutEntryBuilder()
                      .SetBinding(0)
                      .SetVisibility(WGPUShaderStage_Fragment)
                      .SetSamplerBindingLayout(WGPUSamplerBindingType_NonFiltering)
                      .Build())
              .AddLayoutEntry(
                  webgpu::BindGroupLayoutEntryBuilder()
                      .SetBinding(1)
                      .SetVisibility(WGPUShaderStage_Fragment)
                      .SetTextureBindingLayout(WGPUTextureSampleType_UnfilterableFloat)
                      .Build())
              .Build(device)) {
  const webgpu::ShaderModule shader(device, std::filesystem::path("shaders/blit.wgsl"));

  render_pipeline_ =
      webgpu::RenderPipelineBuilder()
          .SetCullMode(WGPUCullMode_None)
          .SetLayout(
              webgpu::PipelineLayoutBuilder().AddBindGroupLayout(bind_group_layout_).Build(device))
          .SetFragmentState(
              webgpu::FragmentStateBuilder()
                  .AddColorTarget(
                      webgpu::ColorTargetStateBuilder()
                          .SetTextureFormat(destination_format)
                          .Build())
                  .SetShader(shader, "fs_main")
                  .Build())
          .SetVertexState(webgpu::VertexStateBuilder().SetShader(shader, "vs_main").Build())
          .Build(device);
}

void BlitRenderer::Blit(
    const webgpu::TextureView &destination,
    const webgpu::TextureView &source,
    const webgpu::Device &device,
    const webgpu::CommandEncoder &command_encoder) {
  const auto bind_group =
      webgpu::BindGroupBuilder()
          .AddBinding(webgpu::BindingBuilder().SetBinding(0).SetSampler(sampler_).Build())
          .AddBinding(webgpu::BindingBuilder().SetBinding(1).SetTextureView(source).Build())
          .SetLayout(bind_group_layout_)
          .Build(device);

  auto render_pass_encoder =
      webgpu::RenderPassEncoderBuilder()
          .AddRenderPassColorAttachment(
              webgpu::RenderPassColorAttachmentBuilder().SetView(destination).Build())
          .Build(command_encoder);

  render_pass_encoder.SetPipeline(render_pipeline_);
  render_pass_encoder.SetBindGroup(0, bind_group);
  render_pass_encoder.Draw(3, 1, 0, 0);
  render_pass_encoder.End();
}

} // namespace rigel::graphics
