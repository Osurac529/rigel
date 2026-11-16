#include <array>
#include <iostream>
#include <string_view>

#include "graphics/graphics.hpp"

using namespace rigel::graphics;

constexpr std::string_view shader_source = R"(
struct VertexInput {
    @location(0) position: vec2f,
    @location(1) color: vec3f,
};

struct VertexOutput {
    @builtin(position) position: vec4f,
    // The location here does not refer to a vertex attribute, it just means
    // that this field must be handled by the rasterizer.
    // (It can also refer to another field of another struct that would be used
    // as input to the fragment shader.)
    @location(0) color: vec3f,
};

@vertex
fn vs_main(in: VertexInput) -> VertexOutput {
    var out: VertexOutput; // create the output struct
    out.position = vec4f(in.position, 0.0, 1.0); // same as what we used to directly return
    out.color = in.color; // forward the color attribute to the fragment shader
    return out;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    return vec4f(pow(in.color, vec3f(2.2)), 1.0); // use the interpolated color coming from the vertex shader
}
)";

const std::vector<float> vertex_data = {
    // x,   y,     r,   g,   b
    -0.5, -0.5, 1.0, 0.0, 0.0, +0.5, -0.5, 0.0, 1.0, 0.0,
    +0.5, +0.5, 0.0, 0.0, 1.0, -0.5, +0.5, 1.0, 1.0, 0.0};

const std::vector<std::uint16_t> index_data = {
    0,
    1,
    2, // Triangle #0 connects points #0, #1 and #2
       // 0, 2, 3, // Triangle #1 connects points #0, #2 and #3
};

const auto vertex_count = static_cast<uint32_t>(vertex_data.size() / 5);

//struct alignas(16) MyStruct {
struct MyStruct {
  alignas(16) float time;
  alignas(16) std::array<float, 4> vec;
};

int main() {
  try {
    Application application;

    std::cout << sizeof(MyStruct) << std::endl;
    std::cout << offsetof(MyStruct, time) << std::endl;
    std::cout << offsetof(MyStruct, vec) << std::endl;

    auto &device = application.device();
    auto queue = device.GetQueue();

    WGPUBufferDescriptor buffer_descriptor = WGPU_BUFFER_DESCRIPTOR_INIT;
    buffer_descriptor.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
    buffer_descriptor.size = vertex_data.size() * sizeof(float);

    Buffer vertex_buffer(device, buffer_descriptor);
    queue.WriteBuffer(vertex_buffer, vertex_data.data());

    // VertexBuffer vertex_buffer(device, vertex_data);

    const auto index_count = static_cast<std::uint32_t>(index_data.size());
    IndexBuffer index_buffer(device, queue, index_data);

    auto pipeline =
        RenderPipelineBuilder()
            .SetFragmentState(
                FragmentStateBuilder()
                    .AddColorTarget(
                        ColorTargetStateBuilder()
                            .SetTextureFormat(application.GetCurrentTexture().GetFormat())
                            .Build())
                    .SetShader(ShaderModule(device, shader_source), "fs_main")
                    .Build())
            .SetVertexState(
                VertexStateBuilder()
                    .AddVertexBufferLayout(
                        VertexBufferLayoutBuilder()
                            .SetStride(5 * sizeof(float))
                            .AddAttribute(WGPUVertexFormat_Float32x2, 0, 0)
                            .AddAttribute(WGPUVertexFormat_Float32x3, 8, 1)
                            .Build())
                    .SetShader(ShaderModule(device, shader_source), "vs_main")
                    .Build())
            .Build(device);

    while (application.IsRunning()) {
      application.PollEvents(
          [](const int key, const float, const float) { std::cout << key << std::endl; });

      auto texture = application.GetCurrentTexture();

      WGPUTextureViewDescriptor texture_view_descriptor = WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT;
      texture_view_descriptor.format = texture.GetFormat();
      texture_view_descriptor.dimension = WGPUTextureViewDimension_2D;
      texture_view_descriptor.baseMipLevel = 0;
      texture_view_descriptor.mipLevelCount = 1;
      texture_view_descriptor.baseArrayLayer = 0;
      texture_view_descriptor.arrayLayerCount = 1;
      texture_view_descriptor.aspect = WGPUTextureAspect_All;

      TextureView texture_view(texture, texture_view_descriptor);

      WGPUCommandEncoderDescriptor command_encoder_descriptor =
          WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT;
      auto command_encoder = device.CreateCommandEncoder(command_encoder_descriptor);

      WGPURenderPassColorAttachment render_pass_color_attachment =
          WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
      render_pass_color_attachment.view = texture_view.native();
      render_pass_color_attachment.loadOp = WGPULoadOp_Clear;
      render_pass_color_attachment.storeOp = WGPUStoreOp_Store;
      render_pass_color_attachment.clearValue = WGPUColor{1.0, 0.0, 0.0, 1.0};

      WGPURenderPassDescriptor render_pass_descriptor = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
      render_pass_descriptor.colorAttachmentCount = 1;
      render_pass_descriptor.colorAttachments = &render_pass_color_attachment;

      auto render_pass = command_encoder.BeginRenderPass(render_pass_descriptor);
      render_pass.SetPipeline(pipeline);
      render_pass.SetIndexBuffer(index_buffer);
      render_pass.SetVertexBuffer(0, vertex_buffer, 0, vertex_buffer.GetSize());
      render_pass.DrawIndexed(index_count, 1, 0, 0, 0);
      render_pass.End();

      auto command_buffer = command_encoder.Finish();

      device.GetQueue().Submit(command_buffer);

      if (WGPUStatus_Success != application.Present()) {
        std::cout << "failed present" << std::endl;
      }
    }
  } catch (const std::exception &exception) {
    std::cout << "Exception: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
