#pragma once

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class RenderPassEncoder : public WGPUObject<
                              WGPURenderPassEncoder,
                              wgpuRenderPassEncoderAddRef,
                              wgpuRenderPassEncoderRelease> {
public:
  using WGPUObject::WGPUObject;

  void End() const;
};

} // namespace rigel::graphics
