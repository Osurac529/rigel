#pragma once

#include <vector>

#include <webgpu/wgpu.h>

namespace webgpu {

class Instance;

class InstanceBuilder {
public:
  InstanceBuilder &SetTimedWaitAnyMaxCount(std::size_t count);

  InstanceBuilder &AddFeatureName(WGPUInstanceFeatureName feature_name);

  Instance Build();

private:
  std::vector<WGPUInstanceFeatureName> feature_names_;
  WGPUInstanceLimits instance_limits_ = WGPU_INSTANCE_LIMITS_INIT;
  WGPUInstanceDescriptor descriptor_ = WGPU_INSTANCE_DESCRIPTOR_INIT;
};

} // namespace webgpu
