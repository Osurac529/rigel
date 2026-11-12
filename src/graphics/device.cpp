#include "graphics/device.hpp"

#include "graphics/command_encoder.hpp"
#include "graphics/graphics_exception.hpp"
#include "graphics/queue.hpp"

namespace rigel::graphics {

Device::Device(WGPUDevice device) : device_(device) {
  if (!device_) {
    throw GraphicsException("Failed to create device.");
  }
}

Device::Device(const Device &other) : device_(other.device_) {
  wgpuDeviceAddRef(device_);
}

Device &Device::operator=(const Device &other) {
  if (this != &other) {
    device_ = other.device_;
    wgpuDeviceAddRef(device_);
  }

  return *this;
}

Device::~Device() {
  wgpuDeviceRelease(device_);
}

WGPULimits Device::GetLimits() const {
  WGPULimits limits = WGPU_LIMITS_INIT;

  if (WGPUStatus_Success != wgpuDeviceGetLimits(device_, &limits)) {
    throw GraphicsException("Device limits retrieval failed.");
  }

  return limits;
}

std::vector<WGPUFeatureName> Device::GetFeatures() const {
  WGPUSupportedFeatures wgpu_features = WGPU_SUPPORTED_FEATURES_INIT;
  wgpuDeviceGetFeatures(device_, &wgpu_features);

  std::vector<WGPUFeatureName> features(wgpu_features.featureCount);

  for (std::size_t i = 0; i < wgpu_features.featureCount; ++i) {
    features[i] = wgpu_features.features[i];
  }

  wgpuSupportedFeaturesFreeMembers(wgpu_features);

  return features;
}

Queue Device::GetQueue() const {
  return Queue(wgpuDeviceGetQueue(device_));
}

CommandEncoder
Device::CreateCommandEncoder(const WGPUCommandEncoderDescriptor &encoder_descriptor) {
  return CommandEncoder(wgpuDeviceCreateCommandEncoder(device_, &encoder_descriptor));
}

const WGPUDevice &Device::native() const {
  return device_;
}

} // namespace rigel::graphics
