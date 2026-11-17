#include <array>
#include <iostream>
#include <string_view>

#include "rigel/application.hpp"

using namespace rigel;
using namespace webgpu;

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

//@group(0) @binding(0) var<uniform> uTime: f32;

@vertex
fn vs_main(in: VertexInput) -> VertexOutput {
    var out: VertexOutput; // create the output struct

    // We now move the scene depending on the time!
    //var offset = vec2f(-0.6875, -0.463);
    //offset += 0.3 * vec2f(cos(uTime), sin(uTime))

    //out.position = vec4f(in.position.x + offset.x, in.position.y + offset.y 0.0, 1.0);
    out.position = vec4f(in.position, 0.0, 1.0);
    out.color = in.color; // forward the color attribute to the fragment shader
    return out;
}

@fragment
fn fs_main(in: VertexOutput) -> @location(0) vec4f {
    return vec4f(pow(in.color, vec3f(2.2)), 1.0); // use the interpolated color coming from the vertex shader
}
)";

const std::vector<float> vertex_data = {
    // clang-format off
    // x,   y,  r,   g,   b
    -0.5, -0.5, 1.0, 0.0, 0.0,
    +0.5, -0.5, 0.0, 1.0, 0.0,
    +0.5, +0.5, 0.0, 0.0, 1.0,
    -0.5, +0.5, 1.0, 1.0, 0.0
    // clang-format on
};

const std::vector<std::uint16_t> index_data = {
    // clang-format off
    0, 1, 2, // Triangle #0 connects points #0, #1 and #2
    0, 2, 3 // Triangle #1 connects points #0, #2 and #3
    // clang-format on
};

const auto vertex_count = static_cast<uint32_t>(vertex_data.size() / 5);

int main() {
  try {
    Application application;

    auto &device = application.device();
    auto queue = device.GetQueue();

    Buffer vertex_buffer(
        device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex,
        vertex_data.size() * sizeof(float));
    queue.WriteBuffer(vertex_buffer, vertex_data.data());

    const auto index_count = static_cast<std::uint32_t>(index_data.size());
    Buffer index_buffer(
        device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index,
        index_data.size() * sizeof(std::uint16_t));
    queue.WriteBuffer(index_buffer, index_data.data());

    float time = 0;
    // uniform buffers must be aligned to 16 bytes
    Buffer uniform_buffer(device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform, 4 * sizeof(float));

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
      ++time;
      queue.WriteBuffer(uniform_buffer, &time);

      application.PollEvents(
          [](const int key, const float, const float) { std::cout << key << std::endl; });

      auto texture = application.GetCurrentTexture();
      auto texture_view = TextureViewBuilder().Build(texture);

      CommandEncoder command_encoder(device);

      auto render_pass = RenderPassEncoderBuilder()
                             .AddRenderPassColorAttachment(
                                 RenderPassColorAttachmentBuilder()
                                     .SetView(texture_view)
                                     .SetClearValue(WGPUColor{1.0, 0.0, 0.0, 1.0})
                                     .Build())
                             .Build(command_encoder);

      render_pass.SetPipeline(pipeline);
      render_pass.SetIndexBuffer(index_buffer, WGPUIndexFormat_Uint16, 0, index_buffer.GetSize());
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
