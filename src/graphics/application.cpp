#include "graphics/application.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#include "graphics/adapter_info.hpp"
#include "graphics/command_buffer.hpp"
#include "graphics/command_encoder.hpp"
#include "graphics/device.hpp"
#include "graphics/queue.hpp"
#include "graphics/render_pass_encoder.hpp"
#include "graphics/surface_configurator.hpp"
#include "graphics/surface_texture.hpp"
#include "graphics/texture_view.hpp"
#include "graphics/window.hpp"

namespace rigel::graphics {

namespace {

Adapter ChooseAdapter(const std::vector<Adapter> &adapters) {
  std::vector<Adapter> adapters_by_type;

  // look for discrete
  for (const auto &adapter : adapters) {
    if (WGPUAdapterType_DiscreteGPU == adapter.GetInfo().adapterType()) {
      adapters_by_type.push_back(adapter);
    }
  }

  if (adapters_by_type.empty()) {
    // look for integrated
    for (const auto &adapter : adapters) {
      if (WGPUAdapterType_IntegratedGPU == adapter.GetInfo().adapterType()) {
        adapters_by_type.push_back(adapter);
      }
    }
  }

  if (adapters_by_type.empty()) {
    // look for CPU
    for (const auto &adapter : adapters) {
      if (WGPUAdapterType_CPU == adapter.GetInfo().adapterType()) {
        adapters_by_type.push_back(adapter);
      }
    }
  }

  // look for vulkan
  std::vector<Adapter> adapters_by_type_backend;

  for (const auto &adapter : adapters_by_type) {
    if (WGPUBackendType_Vulkan == adapter.GetInfo().backendType()) {
      adapters_by_type_backend.push_back(adapter);
    }
  }

  if (adapters_by_type_backend.empty()) {
    // look for platform specific backends
    for (const auto &adapter : adapters_by_type) {
#if defined(_WIN32)
      if (WGPUBackendType_D3D12 == adapter.GetInfo().backendType()) {
        adapters_by_type_backend.push_back(adapter);
      }
#elif defined(__linux__) && !defined(__ANDROID__)
      if (WGPUBackendType_OpenGL == adapter.GetInfo().backendType()) {
        adapters_by_type_backend.push_back(adapter);
      }
#elif defined(__APPLE__)
      if (WGPUBackendType_Metal == adapter.GetInfo().backendType()) {
        adapters_by_type_backend.push_back(adapter);
      }
#elif defined(__linux__) && defined(__ANDROID__)
      if (WGPUBackendType_OpenGLES == adapter.GetInfo().backendType()) {
        adapters_by_type_backend.push_back(adapter);
      }
#endif
    }
  }

  if (adapters_by_type_backend.empty()) {
    // look for lesser platform specific backends
    for (const auto &adapter : adapters_by_type) {
#if defined(_WIN32)
      if (WGPUBackendType_D3D11 == adapter.GetInfo().backendType()) {
        adapters_by_type_backend.push_back(adapter);
      }
#elif defined(__linux__) && !defined(__ANDROID__)
      if (WGPUBackendType_OpenGLES == adapter.GetInfo().backendType()) {
        adapters_by_type_backend.push_back(adapter);
      }
#elif defined(__APPLE__)
      if (WGPUBackendType_OpenGL == adapter.GetInfo().backendType()) {
        adapters_by_type_backend.push_back(adapter);
      }
#endif
    }
  }

  if (adapters_by_type_backend.empty()) {
    // look for lesser platform specific backends
    for (const auto &adapter : adapters_by_type) {
#if defined(_WIN32)
      if (WGPUBackendType_OpenGL == adapter.GetInfo().backendType()) {
        adapters_by_type_backend.push_back(adapter);
      }
#endif
    }
  }

  if (adapters_by_type_backend.empty()) {
    throw GraphicsException("Could not find an adapter.");
  }

  return adapters_by_type_backend.front();
}

void DeviceLost(
    WGPUDevice const *device,
    WGPUDeviceLostReason reason,
    WGPUStringView message,
    WGPU_NULLABLE void *userdata1,
    WGPU_NULLABLE void *userdata2) {
  std::ignore = userdata1;
  std::ignore = userdata2;
  std::ignore = device;

  std::cout << "device lost: " << reason << std::endl;

  if (message.data) {
    std::cout << std::string_view(message.data, message.length) << std::endl;
  }
}

void UncapturedError(
    WGPUDevice const *device,
    WGPUErrorType type,
    WGPUStringView message,
    WGPU_NULLABLE void *userdata1,
    WGPU_NULLABLE void *userdata2) {
  std::ignore = userdata1;
  std::ignore = userdata2;
  std::ignore = device;

  std::cout << "uncaptured error: " << type;

  if (message.data) {
    std::cout << ' ' << std::string_view(message.data, message.length);
  }

  std::cout << std::endl;
}

} // namespace

Application::Application(const ApplicationOptions &options)
    : surface_configuration_(WGPU_SURFACE_CONFIGURATION_INIT) {
#if defined(_WIN32) && defined(_DEBUG)
  AllocConsole();
  FILE *consoleOut;
  freopen_s(&consoleOut, "conout$", "w", stdout);
#endif

  if (!options.instance) {
    instance_ = std::make_unique<Instance>();
  } else {
    instance_ = std::make_unique<Instance>(*options.instance);
  }

  std::optional<Adapter> adapter = options.adapter;

  if (!adapter) {
    adapter = std::make_optional<Adapter>(ChooseAdapter(instance_->EnumerateAdapters()));
  }

  WGPUDeviceDescriptor device_descriptor = WGPU_DEVICE_DESCRIPTOR_INIT;
  device_descriptor.deviceLostCallbackInfo.callback = DeviceLost;
  device_descriptor.uncapturedErrorCallbackInfo.callback = UncapturedError;

  device_ = std::make_unique<Device>(adapter->RequestDevice(device_descriptor));
  window_ = std::make_unique<Window>(options.window_title, options.width, options.height);
  surface_ = std::make_unique<Surface>(instance_->CreateSurface(*window_));

  surface_configuration_.width = window_->GetWidth();
  surface_configuration_.height = window_->GetHeight();
  surface_configuration_.format = surface_->GetPreferredFormat(*adapter);
  surface_configuration_.usage = WGPUTextureUsage_RenderAttachment;
  surface_configuration_.device = device_->native();
  surface_configuration_.presentMode = options.present_mode;
  surface_configuration_.alphaMode = WGPUCompositeAlphaMode_Opaque;

  surface_configurator_ = std::make_unique<SurfaceConfigurator>(*surface_, surface_configuration_);

  window_->SetOnResize([this](const std::uint32_t width, const std::uint32_t height) {
    surface_configuration_.width = width;
    surface_configuration_.height = height;
    surface_configurator_->Configure(surface_configuration_);
  });
}

bool Application::IsRunning() const {
  return !done_;
}

Texture Application::GetCurrentTexture() {
  auto surface_texture = surface_->GetCurrentTexture();

  if (const auto status = surface_texture.status();
      status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal &&
      status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal) {
    surface_configurator_->Configure(surface_configuration_);
  }

  return surface_texture.texture();
}

void Application::PollEvents(
    std::function<void(int key, float mouse_x, float mouse_y)> input_handler) {
#if defined(_WIN32)
  MSG msg;
#elif defined(__linux__)
  xcb_generic_event_t *event = nullptr;
#endif

#if defined(_WIN32)
  while (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
    if (WM_QUIT == msg.message) {
      done_ = true;
    }

    ::TranslateMessage(&msg);

    if (msg.message == WM_KEYDOWN && input_handler) {
      input_handler(static_cast<int>(msg.wParam), 0, 0);
    } else {
      ::DispatchMessageW(&msg);
    }
  }
#elif defined(__linux__)
  while (nullptr != (event = xcb_poll_for_event(connection))) {
    switch (event->response_type & ~0x80) {
    case XCB_EXPOSE: {
      xcb_flush(connection);
      break;
    }

    case XCB_KEY_PRESS: {
      done = true;
      break;
    }
    }

    ::free(event);
  }
#endif

#if defined(__linux__)
  xcb_disconnect(connection);
#endif
}

WGPUStatus Application::Present() {
  return surface_->Present();
}

Device &Application::device() {
  return *device_;
}

} // namespace rigel::graphics
