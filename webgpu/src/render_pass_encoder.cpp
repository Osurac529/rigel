#include "webgpu/render_pass_encoder.hpp"

#include "webgpu/bind_group.hpp"
#include "webgpu/buffer.hpp"
#include "webgpu/render_pipeline.hpp"

namespace webgpu {

void RenderPassEncoder::Draw(
    const std::uint32_t vertex_count,
    const std::uint32_t instance_count,
    const std::uint32_t first_vertex,
    const std::uint32_t first_instance) {
  wgpuRenderPassEncoderDraw(handle(), vertex_count, instance_count, first_vertex, first_instance);
}

void RenderPassEncoder::DrawIndexed(
    const std::uint32_t index_count,
    const std::uint32_t instance_count,
    const std::uint32_t first_index,
    const std::int32_t base_vertex,
    const std::uint32_t first_instance) {
  wgpuRenderPassEncoderDrawIndexed(
      handle(), index_count, instance_count, first_index, base_vertex, first_instance);
}

void RenderPassEncoder::SetPipeline(const RenderPipeline &pipeline) {
  wgpuRenderPassEncoderSetPipeline(handle(), pipeline.handle());
}

void RenderPassEncoder::SetVertexBuffer(
    const std::uint32_t slot,
    const Buffer &buffer,
    const std::uint64_t offset,
    const std::uint64_t size) {
  wgpuRenderPassEncoderSetVertexBuffer(handle(), slot, buffer.handle(), offset, size);
}

void RenderPassEncoder::SetIndexBuffer(
    const Buffer &buffer,
    const WGPUIndexFormat format,
    const std::uint64_t offset,
    const std::uint64_t size) {
  wgpuRenderPassEncoderSetIndexBuffer(handle(), buffer.handle(), format, offset, size);
}

// void RenderPassEncoder::SetIndexBuffer(
//     const IndexBuffer &buffer,
//     const std::uint64_t offset,
//     const std::uint64_t size) {
//   SetIndexBuffer(buffer, buffer.format(), offset, size);
// }
//
// void RenderPassEncoder::SetIndexBuffer(const IndexBuffer &buffer, const std::uint64_t offset) {
//   SetIndexBuffer(buffer, buffer.format(), offset, buffer.GetSize() - offset);
// }

void RenderPassEncoder::SetBindGroup(
    const std::uint32_t group_index,
    const BindGroup &group,
    const std::size_t dynamic_offset_count,
    const std::uint32_t *dynamic_offsets) {
  wgpuRenderPassEncoderSetBindGroup(
      handle(), group_index, group.handle(), dynamic_offset_count, dynamic_offsets);
}

void RenderPassEncoder::End() const {
  wgpuRenderPassEncoderEnd(handle());
}

} // namespace webgpu
