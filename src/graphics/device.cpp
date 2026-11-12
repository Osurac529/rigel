#include "graphics/device.hpp"

#include "graphics/command_encoder.hpp"
#include "graphics/graphics_exception.hpp"
#include "graphics/queue.hpp"

namespace rigel::graphics {

WGPULimits Device::GetLimits() const {
  WGPULimits limits = WGPU_LIMITS_INIT;

  if (WGPUStatus_Success != wgpuDeviceGetLimits(native(), &limits)) {
    throw GraphicsException("Device limits retrieval failed.");
  }

  return limits;
}

std::vector<WGPUFeatureName> Device::GetFeatures() const {
  WGPUSupportedFeatures wgpu_features = WGPU_SUPPORTED_FEATURES_INIT;
  wgpuDeviceGetFeatures(native(), &wgpu_features);

  std::vector<WGPUFeatureName> features(wgpu_features.featureCount);

  for (std::size_t i = 0; i < wgpu_features.featureCount; ++i) {
    features[i] = wgpu_features.features[i];
  }

  wgpuSupportedFeaturesFreeMembers(wgpu_features);

  return features;
}

Queue Device::GetQueue() const {
  return Queue(wgpuDeviceGetQueue(native()));
}

CommandEncoder
Device::CreateCommandEncoder(const WGPUCommandEncoderDescriptor &encoder_descriptor) {
  return CommandEncoder(wgpuDeviceCreateCommandEncoder(native(), &encoder_descriptor));
}

} // namespace rigel::graphics
