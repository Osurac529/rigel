#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class BindGroup : public Object<WGPUBindGroup, wgpuBindGroupAddRef, wgpuBindGroupRelease> {
public:
  using Object::Object;
};

} // namespace webgpu
