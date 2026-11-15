#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class RenderPipeline;
class Buffer;

class RenderPassEncoder : public WGPUObject<
                              WGPURenderPassEncoder,
                              wgpuRenderPassEncoderAddRef,
                              wgpuRenderPassEncoderRelease> {
public:
  using WGPUObject::WGPUObject;

  void Draw(
      std::uint32_t vertex_count,
      std::uint32_t instanc_cCount,
      std::uint32_t first_vertex,
      std::uint32_t first_instance);

  void DrawIndexed(
      std::uint32_t index_count,
      std::uint32_t instance_count,
      std::uint32_t first_index,
      std::int32_t base_vertex,
      std::uint32_t first_instance);

  void SetPipeline(const RenderPipeline &pipeline);

  void SetVertexBuffer(
      std::uint32_t slot,
      const Buffer &buffer,
      std::uint64_t offset,
      std::uint64_t size);

  void SetIndexBuffer(
      const Buffer &buffer,
      WGPUIndexFormat format,
      std::uint64_t offset,
      std::uint64_t size);

  void End() const;
};

} // namespace rigel::graphics
