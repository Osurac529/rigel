#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class PipelineLayout
    : public Object<WGPUPipelineLayout, wgpuPipelineLayoutAddRef, wgpuPipelineLayoutRelease> {
public:
  using Object::Object;
};

} // namespace webgpu
