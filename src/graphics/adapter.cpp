#include "graphics/adapter.hpp"

#include <iostream>

#include "graphics/adapter_info.hpp"
#include "graphics/device.hpp"
#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

namespace {

struct CallbackUserdata {
  WGPUDevice device = nullptr;
  bool complete = false;
};

void DeviceCallback(
    WGPURequestDeviceStatus status,
    WGPUDevice device,
    WGPUStringView message,
    WGPU_NULLABLE void *userdata1,
    WGPU_NULLABLE void *userdata2) {
  std::ignore = userdata2;
  auto &callback_userdata = *reinterpret_cast<CallbackUserdata *>(userdata1);

  if (WGPURequestDeviceStatus_Success == status) {
    callback_userdata.device = device;
  } else if (message.data) {
    std::cout << "Device callback error: " << std::string_view(message.data, message.length)
              << std::endl;
  }

  callback_userdata.complete = true;
}

} // namespace

Device Adapter::RequestDevice(const WGPUDeviceDescriptor &descriptor) const {
  WGPURequestDeviceCallbackInfo callback_info = WGPU_REQUEST_DEVICE_CALLBACK_INFO_INIT;
  callback_info.callback = DeviceCallback;
  CallbackUserdata user_data;
  callback_info.userdata1 = &user_data;

  wgpuAdapterRequestDevice(native(), &descriptor, callback_info);

  if (!user_data.complete) {
    throw GraphicsException("Device request callback did not happen.");
  }

  return Device(user_data.device);
}

AdapterInfo Adapter::GetInfo() const {
  return AdapterInfo(native());
}

WGPULimits Adapter::GetLimits() const {
  WGPULimits limits = WGPU_LIMITS_INIT;

  if (WGPUStatus_Success != wgpuAdapterGetLimits(native(), &limits)) {
    throw GraphicsException("Adapter limits retrieval failed.");
  }

  return limits;
}

std::vector<WGPUFeatureName> Adapter::GetFeatures() const {
  WGPUSupportedFeatures wgpu_features = WGPU_SUPPORTED_FEATURES_INIT;
  wgpuAdapterGetFeatures(native(), &wgpu_features);

  std::vector<WGPUFeatureName> features(wgpu_features.featureCount);

  for (std::size_t i = 0; i < wgpu_features.featureCount; ++i) {
    features[i] = wgpu_features.features[i];
  }

  wgpuSupportedFeaturesFreeMembers(wgpu_features);

  return features;
}

} // namespace rigel::graphics
