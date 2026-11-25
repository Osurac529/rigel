#include "webgpu/device_builder.hpp"

#include <sstream>

#include "webgpu/adapter.hpp"
#include "webgpu/device.hpp"
#include "webgpu/exception.hpp"

namespace webgpu {

namespace {

struct CallbackUserdata {
  WGPUDevice device = nullptr;
  bool complete = false;
};

void DeviceCallback(
    WGPURequestDeviceStatus status,
    WGPUDevice device,
    WGPUStringView message,
    WGPU_NULLABLE void *userdata1,
    WGPU_NULLABLE void *userdata2) {
  std::ignore = userdata2;
  auto &callback_userdata = *reinterpret_cast<CallbackUserdata *>(userdata1);

  if (WGPURequestDeviceStatus_Success == status) {
    callback_userdata.device = device;
  } else {

    std::ostringstream oss;

    oss << "Device callback error: status: " << status;

    if (message.data) {
      oss << " message: " << std::string_view(message.data, message.length);
    }

    throw Exception(oss.str());
  }

  callback_userdata.complete = true;
}

} // namespace

DeviceBuilder &DeviceBuilder::AddRequiredFeatureName(const WGPUFeatureName feature_name) {
  required_features_.push_back(feature_name);
  return *this;
}

DeviceBuilder &DeviceBuilder::RegisterDeviceLostCallback(
    const WGPUDeviceLostCallback &callback,
    void *userdata1,
    void *userdata2) {
  descriptor_.deviceLostCallbackInfo.callback = callback;
  descriptor_.deviceLostCallbackInfo.userdata1 = userdata1;
  descriptor_.deviceLostCallbackInfo.userdata2 = userdata2;

  return *this;
}

DeviceBuilder &DeviceBuilder::RegisterUncapturedErrorCallback(
    const WGPUUncapturedErrorCallback &callback,
    void *userdata1,
    void *userdata2) {
  descriptor_.uncapturedErrorCallbackInfo.callback = callback;
  descriptor_.uncapturedErrorCallbackInfo.userdata1 = userdata1;
  descriptor_.uncapturedErrorCallbackInfo.userdata2 = userdata2;

  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxTextureDimension1D(const std::uint32_t value) {
  limits_.maxTextureDimension1D = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxTextureDimension2D(const std::uint32_t value) {
  limits_.maxTextureDimension2D = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxTextureDimension3D(const std::uint32_t value) {
  limits_.maxTextureDimension3D = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxTextureArrayLayers(const std::uint32_t value) {
  limits_.maxTextureArrayLayers = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxBindGroups(const std::uint32_t value) {
  limits_.maxBindGroups = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxBindGroupsPlusVertexBuffers(const std::uint32_t value) {
  limits_.maxBindGroupsPlusVertexBuffers = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxBindingsPerBindGroup(const std::uint32_t value) {
  limits_.maxBindingsPerBindGroup = value;
  return *this;
}

DeviceBuilder &
DeviceBuilder::SetMaxDynamicUniformBuffersPerPipelineLayout(const std::uint32_t value) {
  limits_.maxDynamicUniformBuffersPerPipelineLayout = value;
  return *this;
}

DeviceBuilder &
DeviceBuilder::SetMaxDynamicStorageBuffersPerPipelineLayout(const std::uint32_t value) {
  limits_.maxDynamicStorageBuffersPerPipelineLayout = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxSampledTexturesPerShaderStage(const std::uint32_t value) {
  limits_.maxSampledTexturesPerShaderStage = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxSamplersPerShaderStage(const std::uint32_t value) {
  limits_.maxSamplersPerShaderStage = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxStorageBuffersPerShaderStage(const std::uint32_t value) {
  limits_.maxStorageBuffersPerShaderStage = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxStorageTexturesPerShaderStage(const std::uint32_t value) {
  limits_.maxStorageTexturesPerShaderStage = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxUniformBuffersPerShaderStage(const std::uint32_t value) {
  limits_.maxUniformBuffersPerShaderStage = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxUniformBufferBindingSize(const std::uint64_t value) {
  limits_.maxUniformBufferBindingSize = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxStorageBufferBindingSize(const std::uint64_t value) {
  limits_.maxStorageBufferBindingSize = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMinUniformBufferOffsetAlignment(const std::uint32_t value) {
  limits_.minUniformBufferOffsetAlignment = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMinStorageBufferOffsetAlignment(const std::uint32_t value) {
  limits_.minStorageBufferOffsetAlignment = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxVertexBuffers(const std::uint32_t value) {
  limits_.maxVertexBuffers = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxBufferSize(const std::uint64_t value) {
  limits_.maxBufferSize = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxVertexAttributes(const std::uint32_t value) {
  limits_.maxVertexAttributes = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxVertexBufferArrayStride(const std::uint32_t value) {
  limits_.maxVertexBufferArrayStride = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxInterStageShaderVariables(const std::uint32_t value) {
  limits_.maxInterStageShaderVariables = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxColorAttachments(const std::uint32_t value) {
  limits_.maxColorAttachments = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxColorAttachmentBytesPerSample(const std::uint32_t value) {
  limits_.maxColorAttachmentBytesPerSample = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxComputeWorkgroupStorageSize(const std::uint32_t value) {
  limits_.maxComputeWorkgroupStorageSize = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxComputeInvocationsPerWorkgroup(const std::uint32_t value) {
  limits_.maxComputeInvocationsPerWorkgroup = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxComputeWorkgroupSizeX(const std::uint32_t value) {
  limits_.maxComputeWorkgroupSizeX = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxComputeWorkgroupSizeY(const std::uint32_t value) {
  limits_.maxComputeWorkgroupSizeY = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxComputeWorkgroupSizeZ(const std::uint32_t value) {
  limits_.maxComputeWorkgroupSizeZ = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxComputeWorkgroupsPerDimension(const std::uint32_t value) {
  limits_.maxComputeWorkgroupsPerDimension = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetMaxImmediateSize(const std::uint32_t value) {
  limits_.maxImmediateSize = value;
  return *this;
}

DeviceBuilder &DeviceBuilder::SetLimits(const WGPULimits &limits) {
  limits_ = limits;

  return *this;
}

Device DeviceBuilder::Build(const Adapter &adapter) {
  descriptor_.requiredFeatureCount = required_features_.size();
  descriptor_.requiredFeatures = required_features_.data();
  descriptor_.requiredLimits = &limits_;

  WGPURequestDeviceCallbackInfo callback_info = WGPU_REQUEST_DEVICE_CALLBACK_INFO_INIT;
  callback_info.callback = DeviceCallback;
  CallbackUserdata user_data;
  callback_info.userdata1 = &user_data;

  wgpuAdapterRequestDevice(adapter.handle(), &descriptor_, callback_info);

  if (!user_data.complete) {
    throw Exception("Device request callback did not happen.");
  }

  return Device(user_data.device);
}

} // namespace webgpu
