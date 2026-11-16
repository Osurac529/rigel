#include "webgpu/shader_module.hpp"

#include <fstream>

#include "webgpu/device.hpp"

namespace webgpu {

namespace {

WGPUShaderModule Create(Device &device, std::string_view code) {
  WGPUShaderSourceWGSL shader_source = WGPU_SHADER_SOURCE_WGSL_INIT;
  shader_source.chain.sType = WGPUSType_ShaderSourceWGSL;
  shader_source.code.data = code.data();
  shader_source.code.length = code.length();

  WGPUShaderModuleDescriptor descriptor = WGPU_SHADER_MODULE_DESCRIPTOR_INIT;
  descriptor.nextInChain = &shader_source.chain;

  return wgpuDeviceCreateShaderModule(device.handle(), &descriptor);
}

WGPUShaderModule Create(Device &device, const std::filesystem::path &path) {
  WGPUShaderSourceWGSL shader_source = WGPU_SHADER_SOURCE_WGSL_INIT;
  shader_source.chain.sType = WGPUSType_ShaderSourceWGSL;

  WGPUShaderModuleDescriptor descriptor = WGPU_SHADER_MODULE_DESCRIPTOR_INIT;
  descriptor.nextInChain = &shader_source.chain;

  std::ifstream stream(path);
  stream.exceptions(std::ifstream::failbit | std::ifstream::eofbit | std::ifstream::badbit);

  std::stringstream buffer;
  buffer << stream.rdbuf();
  const auto contents = buffer.str();

  shader_source.code.data = contents.c_str();
  shader_source.code.length = contents.length();

  return wgpuDeviceCreateShaderModule(device.handle(), &descriptor);
}

} // namespace

ShaderModule::ShaderModule(Device &device, std::string_view code)
    : ShaderModule(Create(device, code)) {}

ShaderModule::ShaderModule(Device &device, const std::filesystem::path &path)
    : ShaderModule(Create(device, path)) {}

} // namespace webgpu
