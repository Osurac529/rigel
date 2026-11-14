#include "graphics/shader_module.hpp"

#include "graphics/device.hpp"

namespace rigel::graphics {

namespace {

WGPUShaderModule CreateShader(Device &device, std::string_view code) {
  WGPUShaderSourceWGSL shader_source = WGPU_SHADER_SOURCE_WGSL_INIT;
  shader_source.chain.sType = WGPUSType_ShaderSourceWGSL;
  shader_source.code.data = code.data();
  shader_source.code.length = code.length();

  WGPUShaderModuleDescriptor descriptor = WGPU_SHADER_MODULE_DESCRIPTOR_INIT;
  descriptor.nextInChain = &shader_source.chain;

  return wgpuDeviceCreateShaderModule(device.native(), &descriptor);
}

} // namespace

ShaderModule::ShaderModule(Device &device, std::string_view code)
    : ShaderModule(CreateShader(device, code)) {}

} // namespace rigel::graphics
