#pragma once

#include <cstdint>

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class RenderPipeline;

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

  void SetPipeline(const RenderPipeline &pipeline);

  void End() const;
};

} // namespace rigel::graphics
