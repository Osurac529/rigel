#include "webgpu/adapter.hpp"

#include "webgpu/adapter_info.hpp"
#include "webgpu/exception.hpp"

namespace webgpu {

AdapterInfo Adapter::GetInfo() const {
  return AdapterInfo(*this);
}

WGPULimits Adapter::GetLimits() const {
  WGPULimits limits = WGPU_LIMITS_INIT;

  if (WGPUStatus_Success != wgpuAdapterGetLimits(handle(), &limits)) {
    throw Exception("Adapter limits retrieval failed.");
  }

  return limits;
}

std::vector<WGPUFeatureName> Adapter::GetFeatures() const {
  WGPUSupportedFeatures wgpu_features = WGPU_SUPPORTED_FEATURES_INIT;
  wgpuAdapterGetFeatures(handle(), &wgpu_features);

  std::vector<WGPUFeatureName> features(wgpu_features.featureCount);

  for (std::size_t i = 0; i < wgpu_features.featureCount; ++i) {
    features[i] = wgpu_features.features[i];
  }

  wgpuSupportedFeaturesFreeMembers(wgpu_features);

  return features;
}

} // namespace webgpu
