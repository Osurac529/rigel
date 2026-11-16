#include "graphics/render_pass_encoder.hpp"

#include "graphics/buffer.hpp"
#include "graphics/render_pipeline.hpp"

namespace rigel::graphics {

void RenderPassEncoder::Draw(
    const std::uint32_t vertex_count,
    const std::uint32_t instance_count,
    const std::uint32_t first_vertex,
    const std::uint32_t first_instance) {
  wgpuRenderPassEncoderDraw(native(), vertex_count, instance_count, first_vertex, first_instance);
}

void RenderPassEncoder::DrawIndexed(
    const std::uint32_t index_count,
    const std::uint32_t instance_count,
    const std::uint32_t first_index,
    const std::int32_t base_vertex,
    const std::uint32_t first_instance) {
  wgpuRenderPassEncoderDrawIndexed(
      native(), index_count, instance_count, first_index, base_vertex, first_instance);
}

void RenderPassEncoder::SetPipeline(const RenderPipeline &pipeline) {
  wgpuRenderPassEncoderSetPipeline(native(), pipeline.native());
}

void RenderPassEncoder::SetVertexBuffer(
    const std::uint32_t slot,
    const Buffer &buffer,
    const std::uint64_t offset,
    const std::uint64_t size) {
  wgpuRenderPassEncoderSetVertexBuffer(native(), slot, buffer.native(), offset, size);
}

void RenderPassEncoder::SetIndexBuffer(
    const Buffer &buffer,
    const WGPUIndexFormat format,
    const std::uint64_t offset,
    const std::uint64_t size) {
  wgpuRenderPassEncoderSetIndexBuffer(native(), buffer.native(), format, offset, size);
}

void RenderPassEncoder::SetIndexBuffer(
    const IndexBuffer &buffer,
    const std::uint64_t offset,
    const std::uint64_t size) {
  SetIndexBuffer(buffer, buffer.format(), offset, size);
}

void RenderPassEncoder::SetIndexBuffer(const IndexBuffer &buffer, const std::uint64_t offset) {
  SetIndexBuffer(buffer, buffer.format(), offset, buffer.GetSize() - offset);
}

void RenderPassEncoder::End() const {
  wgpuRenderPassEncoderEnd(native());
}

} // namespace rigel::graphics
