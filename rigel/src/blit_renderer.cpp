#include "rigel/graphics/blit_renderer.hpp"

namespace rigel::graphics {

void Blit(
    const webgpu::TextureView &destination,
    const WGPUTextureFormat destination_format,
    const webgpu::TextureView &source,
    const webgpu::Device &device,
    const webgpu::CommandEncoder& command_encoder) {
  auto sampler = webgpu::SamplerBuilder()
                     .SetMagFilter(WGPUFilterMode_Nearest)
                     .SetMinFilter(WGPUFilterMode_Nearest)
                     .SetMipmapFilter(WGPUMipmapFilterMode_Nearest)
                     .Build(device);

  const auto bind_group_layout =
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
          .Build(device);

  const auto bind_group =
      webgpu::BindGroupBuilder()
          .AddBinding(webgpu::BindingBuilder().SetBinding(0).SetSampler(sampler).Build())
          .AddBinding(webgpu::BindingBuilder().SetBinding(1).SetTextureView(source).Build())
          .SetLayout(bind_group_layout)
          .Build(device);

  const webgpu::ShaderModule shader(device, std::filesystem::path("shaders/blit.wgsl"));

  const auto render_pipeline =
      webgpu::RenderPipelineBuilder()
          .SetCullMode(WGPUCullMode_None)
          .SetLayout(
              webgpu::PipelineLayoutBuilder().AddBindGroupLayout(bind_group_layout).Build(device))
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

  //webgpu::CommandEncoder command_encoder(device);

  auto render_pass_encoder =
      webgpu::RenderPassEncoderBuilder()
          .AddRenderPassColorAttachment(
              webgpu::RenderPassColorAttachmentBuilder().SetView(destination).Build())
          .Build(command_encoder);

  render_pass_encoder.SetPipeline(render_pipeline);
  render_pass_encoder.SetBindGroup(0, bind_group);
  render_pass_encoder.Draw(3, 1, 0, 0);
  render_pass_encoder.End();

  //device.GetQueue().Submit(command_encoder.Finish());
}

} // namespace rigel::graphics
