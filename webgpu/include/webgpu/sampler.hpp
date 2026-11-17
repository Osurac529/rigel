#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class Sampler : public Object<WGPUSampler, wgpuSamplerAddRef, wgpuSamplerRelease> {
public:
  using Object::Object;
};

} // namespace webgpu
