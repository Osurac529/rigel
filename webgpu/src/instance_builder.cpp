#include "webgpu/instance_builder.hpp"

#include "webgpu/instance.hpp"

namespace webgpu {

InstanceBuilder &InstanceBuilder::SetTimedWaitAnyMaxCount(const std::size_t count) {
  instance_limits_.timedWaitAnyMaxCount = count;

  return *this;
}

InstanceBuilder &InstanceBuilder::AddFeatureName(const WGPUInstanceFeatureName feature_name) {
  feature_names_.push_back(feature_name);

  return *this;
}

Instance InstanceBuilder::Build() {
  descriptor_.requiredFeatureCount = feature_names_.size();
  descriptor_.requiredFeatures = feature_names_.data();
  descriptor_.requiredLimits = &instance_limits_;

  return Instance(wgpuCreateInstance(&descriptor_));
}

} // namespace webgpu
