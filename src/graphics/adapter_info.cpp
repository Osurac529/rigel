#include "graphics/adapter_info.hpp"

#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

AdapterInfo::AdapterInfo(WGPUAdapter adapter) {
  if (WGPUStatus_Success != wgpuAdapterGetInfo(adapter, &adapter_info_)) {
    throw GraphicsException("Adapter information retrieval failed.");
  }
}

AdapterInfo::~AdapterInfo() {
  wgpuAdapterInfoFreeMembers(adapter_info_);
}

std::string_view AdapterInfo::vendor() const {
  return std::string_view(adapter_info_.vendor.data, adapter_info_.vendor.length);
}

std::string_view AdapterInfo::architecture() const {
  return std::string_view(adapter_info_.architecture.data, adapter_info_.architecture.length);
}

std::string_view AdapterInfo::device() const {
  return std::string_view(adapter_info_.device.data, adapter_info_.device.length);
}

std::string_view AdapterInfo::description() const {
  return std::string_view(adapter_info_.description.data, adapter_info_.description.length);
}

WGPUBackendType AdapterInfo::backendType() const {
  return adapter_info_.backendType;
}

WGPUAdapterType AdapterInfo::adapterType() const {
  return adapter_info_.adapterType;
}

std::uint32_t AdapterInfo::vendorID() const {
  return adapter_info_.vendorID;
}

std::uint32_t AdapterInfo::deviceID() const {
  return adapter_info_.deviceID;
}

std::uint32_t AdapterInfo::subgroupMinSize() const {
  return adapter_info_.subgroupMinSize;
}

std::uint32_t AdapterInfo::subgroupMaxSize() const {
  return adapter_info_.subgroupMaxSize;
}

} // namespace rigel::graphics
