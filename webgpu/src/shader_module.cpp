#include "webgpu/shader_module.hpp"

#include <fstream>

#include "webgpu/device.hpp"

namespace webgpu {

namespace {

WGPUShaderModule CreateFromCode(Device &device, std::string_view code) {
  WGPUShaderSourceWGSL shader_source = WGPU_SHADER_SOURCE_WGSL_INIT;
  shader_source.chain.sType = WGPUSType_ShaderSourceWGSL;
  shader_source.code.data = code.data();
  shader_source.code.length = code.length();

  WGPUShaderModuleDescriptor descriptor = WGPU_SHADER_MODULE_DESCRIPTOR_INIT;
  descriptor.nextInChain = &shader_source.chain;

  return wgpuDeviceCreateShaderModule(device.handle(), &descriptor);
}

WGPUShaderModule CreateFromPath(Device &device, const std::filesystem::path &path) {
  std::ifstream stream(path);
  stream.exceptions(std::ifstream::failbit | std::ifstream::eofbit | std::ifstream::badbit);

  std::stringstream buffer;
  buffer << stream.rdbuf();
  const auto contents = buffer.str();

  return CreateFromCode(device, contents);
}

} // namespace

ShaderModule::ShaderModule(Device &device, std::string_view code)
    : ShaderModule(CreateFromCode(device, code)) {}

ShaderModule::ShaderModule(Device &device, const std::filesystem::path &path)
    : ShaderModule(CreateFromPath(device, path)) {}

} // namespace webgpu
