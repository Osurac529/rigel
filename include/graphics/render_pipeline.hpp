#pragma once

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class Device;

class RenderPipeline
    : public WGPUObject<WGPURenderPipeline, wgpuRenderPipelineAddRef, wgpuRenderPipelineRelease> {
public:
  using WGPUObject::WGPUObject;

  explicit RenderPipeline(Device &device, const WGPURenderPipelineDescriptor &descriptor);
};

} // namespace rigel::graphics
