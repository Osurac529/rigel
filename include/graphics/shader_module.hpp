#pragma once

#include <string_view>

#include <webgpu/wgpu.h>

#include "graphics/wgpu_object.hpp"

namespace rigel::graphics {

class Device;

class ShaderModule
    : public WGPUObject<WGPUShaderModule, wgpuShaderModuleAddRef, wgpuShaderModuleRelease> {
public:
  using WGPUObject::WGPUObject;

  explicit ShaderModule(Device &device, std::string_view code);

private:
};

} // namespace rigel::graphics
