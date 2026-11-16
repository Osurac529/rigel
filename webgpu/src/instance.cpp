#include "webgpu/instance.hpp"

namespace webgpu {

std::vector<Adapter>
Instance::EnumerateAdapters(const WGPUInstanceEnumerateAdapterOptions &options) const {
  const auto num_adapters = wgpuInstanceEnumerateAdapters(handle(), &options, nullptr);

  std::vector<WGPUAdapter> wgpu_adapters(num_adapters);

  wgpuInstanceEnumerateAdapters(handle(), &options, wgpu_adapters.data());

  return {wgpu_adapters.begin(), wgpu_adapters.end()};
}

} // namespace webgpu
