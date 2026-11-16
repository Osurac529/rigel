#include "webgpu/device.hpp"

// #include "webgpu/command_encoder.hpp"
#include "webgpu/exception.hpp"
#include "webgpu/queue.hpp"
// #include "webgpu/render_pipeline.hpp"

namespace webgpu {

WGPULimits Device::GetLimits() const {
  WGPULimits limits = WGPU_LIMITS_INIT;

  if (WGPUStatus_Success != wgpuDeviceGetLimits(handle(), &limits)) {
    throw Exception("Device limits retrieval failed.");
  }

  return limits;
}

std::vector<WGPUFeatureName> Device::GetFeatures() const {
  WGPUSupportedFeatures wgpu_features = WGPU_SUPPORTED_FEATURES_INIT;
  wgpuDeviceGetFeatures(handle(), &wgpu_features);

  std::vector<WGPUFeatureName> features(wgpu_features.featureCount);

  for (std::size_t i = 0; i < wgpu_features.featureCount; ++i) {
    features[i] = wgpu_features.features[i];
  }

  wgpuSupportedFeaturesFreeMembers(wgpu_features);

  return features;
}

Queue Device::GetQueue() const {
  return Queue(wgpuDeviceGetQueue(handle()));
}

} // namespace webgpu
