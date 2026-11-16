#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class TextureView : public Object<WGPUTextureView, wgpuTextureViewAddRef, wgpuTextureViewRelease> {
public:
  using Object::Object;
};

} // namespace webgpu
