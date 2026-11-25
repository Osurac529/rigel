#pragma once

#include <cstdint>
#include <vector>

#include <webgpu/wgpu.h>

namespace webgpu {

class Device;
class Adapter;

class DeviceBuilder {
public:
  DeviceBuilder &AddRequiredFeatureName(WGPUFeatureName feature_name);

  DeviceBuilder &RegisterDeviceLostCallback(
      const WGPUDeviceLostCallback &callback,
      void *userdata1 = nullptr,
      void *userdata2 = nullptr);

  DeviceBuilder &RegisterUncapturedErrorCallback(
      const WGPUUncapturedErrorCallback &callback,
      void *userdata1 = nullptr,
      void *userdata2 = nullptr);

  DeviceBuilder &SetMaxTextureDimension1D(std::uint32_t value);

  DeviceBuilder &SetMaxTextureDimension2D(std::uint32_t value);

  DeviceBuilder &SetMaxTextureDimension3D(std::uint32_t value);

  DeviceBuilder &SetMaxTextureArrayLayers(std::uint32_t value);

  DeviceBuilder &SetMaxBindGroups(std::uint32_t value);

  DeviceBuilder &SetMaxBindGroupsPlusVertexBuffers(std::uint32_t value);

  DeviceBuilder &SetMaxBindingsPerBindGroup(std::uint32_t value);

  DeviceBuilder &SetMaxDynamicUniformBuffersPerPipelineLayout(std::uint32_t value);

  DeviceBuilder &SetMaxDynamicStorageBuffersPerPipelineLayout(std::uint32_t value);

  DeviceBuilder &SetMaxSampledTexturesPerShaderStage(std::uint32_t value);

  DeviceBuilder &SetMaxSamplersPerShaderStage(std::uint32_t value);

  DeviceBuilder &SetMaxStorageBuffersPerShaderStage(std::uint32_t value);

  DeviceBuilder &SetMaxStorageTexturesPerShaderStage(std::uint32_t value);

  DeviceBuilder &SetMaxUniformBuffersPerShaderStage(std::uint32_t value);

  DeviceBuilder &SetMaxUniformBufferBindingSize(std::uint64_t value);

  DeviceBuilder &SetMaxStorageBufferBindingSize(std::uint64_t value);

  DeviceBuilder &SetMinUniformBufferOffsetAlignment(std::uint32_t value);

  DeviceBuilder &SetMinStorageBufferOffsetAlignment(std::uint32_t value);

  DeviceBuilder &SetMaxVertexBuffers(std::uint32_t value);

  DeviceBuilder &SetMaxBufferSize(std::uint64_t value);

  DeviceBuilder &SetMaxVertexAttributes(std::uint32_t value);

  DeviceBuilder &SetMaxVertexBufferArrayStride(std::uint32_t value);

  DeviceBuilder &SetMaxInterStageShaderVariables(std::uint32_t value);

  DeviceBuilder &SetMaxColorAttachments(std::uint32_t value);

  DeviceBuilder &SetMaxColorAttachmentBytesPerSample(std::uint32_t value);

  DeviceBuilder &SetMaxComputeWorkgroupStorageSize(std::uint32_t value);

  DeviceBuilder &SetMaxComputeInvocationsPerWorkgroup(std::uint32_t value);

  DeviceBuilder &SetMaxComputeWorkgroupSizeX(std::uint32_t value);

  DeviceBuilder &SetMaxComputeWorkgroupSizeY(std::uint32_t value);

  DeviceBuilder &SetMaxComputeWorkgroupSizeZ(std::uint32_t value);

  DeviceBuilder &SetMaxComputeWorkgroupsPerDimension(std::uint32_t value);

  DeviceBuilder &SetMaxImmediateSize(std::uint32_t value);

  DeviceBuilder &SetLimits(const WGPULimits &limits);

  Device Build(const Adapter &adapter);

private:
  std::vector<WGPUFeatureName> required_features_;
  WGPULimits limits_ = WGPU_LIMITS_INIT;
  WGPUDeviceDescriptor descriptor_ = WGPU_DEVICE_DESCRIPTOR_INIT;
};

} // namespace webgpu
