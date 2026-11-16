#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class Device;

class RenderPipeline
    : public Object<WGPURenderPipeline, wgpuRenderPipelineAddRef, wgpuRenderPipelineRelease> {
public:
  using Object::Object;
};

} // namespace webgpu
