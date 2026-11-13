#pragma once

#include <cstdint>
#include <string_view>

#include <webgpu/wgpu.h>

#include "utilities/move_only.hpp"

namespace rigel::graphics {

class AdapterInfo : private utilities::MoveOnly {
public:
  explicit AdapterInfo(WGPUAdapter adapter);

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

} // namespace rigel::graphics
