#pragma once

#include <filesystem>
#include <string_view>

#include <webgpu/wgpu.h>

#include "webgpu/object.hpp"

namespace webgpu {

class Device;

class ShaderModule
    : public Object<WGPUShaderModule, wgpuShaderModuleAddRef, wgpuShaderModuleRelease> {
public:
  using Object::Object;

  explicit ShaderModule(Device &device, std::string_view code);

  explicit ShaderModule(Device &device, const std::filesystem::path &path);

private:
};

} // namespace webgpu
