#include "graphics/render_pass_encoder.hpp"

#include "graphics/render_pipeline.hpp"

namespace rigel::graphics {

void RenderPassEncoder::Draw(
    const std::uint32_t vertex_count,
    const std::uint32_t instance_count,
    const std::uint32_t first_vertex,
    const std::uint32_t first_instance) {
  wgpuRenderPassEncoderDraw(native(), vertex_count, instance_count, first_vertex, first_instance);
}

void RenderPassEncoder::SetPipeline(const RenderPipeline &pipeline) {
  wgpuRenderPassEncoderSetPipeline(native(), pipeline.native());
}

void RenderPassEncoder::End() const {
  wgpuRenderPassEncoderEnd(native());
}

} // namespace rigel::graphics
