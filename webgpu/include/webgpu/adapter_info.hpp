#pragma once

#include <cstdint>
#include <string_view>

#include <webgpu/wgpu.h>

namespace webgpu {

class Adapter;

class AdapterInfo {
public:
  explicit AdapterInfo(const Adapter &adapter);

  AdapterInfo(const AdapterInfo &) = delete;
  AdapterInfo &operator=(const AdapterInfo &) = delete;

  AdapterInfo(AdapterInfo &&) = default;
  AdapterInfo &operator=(AdapterInfo &&) = default;

  ~AdapterInfo();

  std::string_view vendor() const;

  std::string_view architecture() const;

  std::string_view device() const;

  std::string_view description() const;

  WGPUBackendType backendType() const;

  WGPUAdapterType adapterType() const;

  std::uint32_t vendorID() const;

  std::uint32_t deviceID() const;

  std::uint32_t subgroupMinSize() const;

  std::uint32_t subgroupMaxSize() const;

private:
  WGPUAdapterInfo adapter_info_;
};

} // namespace webgpu
