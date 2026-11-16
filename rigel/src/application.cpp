#include "rigel/application.hpp"

#include <sstream>
#include <string_view>

#ifdef _WIN32
#include <windows.h>
#endif

#include "rigel/window.hpp"
#include "webgpu/adapter_info.hpp"
#include "webgpu/command_buffer.hpp"
#include "webgpu/command_encoder.hpp"
#include "webgpu/device.hpp"
#include "webgpu/queue.hpp"
#include "webgpu/render_pass_encoder.hpp"
#include "webgpu/surface_configurator.hpp"
#include "webgpu/surface_texture.hpp"
#include "webgpu/texture_view.hpp"

namespace rigel {

namespace {

webgpu::Adapter ChooseAdapter(const std::vector<webgpu::Adapter> &adapters) {
  std::vector<webgpu::Adapter> adapters_by_type;

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
  std::vector<webgpu::Adapter> adapters_by_type_backend;

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
    throw std::runtime_error("Could not find an adapter.");
  }

  return adapters_by_type_backend.front();
}

void DeviceLost(
    WGPUDevice const *device,
    WGPUDeviceLostReason reason,
    WGPUStringView message,
    WGPU_NULLABLE void *userdata1,
    WGPU_NULLABLE void *userdata2) {
  std::ignore = userdata2;
  std::ignore = device;

  std::ostringstream oss;
  oss << "device lost: " << reason;

  if (message.data) {
    oss << " message: " << std::string_view(message.data, message.length);
  }

  *reinterpret_cast<std::string *>(userdata1) = oss.str();
}

void UncapturedError(
    WGPUDevice const *device,
    WGPUErrorType type,
    WGPUStringView message,
    WGPU_NULLABLE void *userdata1,
    WGPU_NULLABLE void *userdata2) {
  std::ignore = userdata2;
  std::ignore = device;

  std::ostringstream oss;
  oss << "uncaptured error: " << type;

  if (message.data) {
    oss << " message: " << std::string_view(message.data, message.length);
  }

  *reinterpret_cast<std::string *>(userdata1) = oss.str();
}

WGPUSurfaceConfiguration CreateSurfaceConfiguration(
    const Window &window,
    const webgpu::Adapter &adapter,
    const webgpu::Surface &surface,
    const webgpu::Device &device,
    const ApplicationOptions &options) {
  WGPUSurfaceConfiguration surface_configuration = WGPU_SURFACE_CONFIGURATION_INIT;

  surface_configuration.width = window.GetWidth();
  surface_configuration.height = window.GetHeight();
  surface_configuration.format = surface.GetPreferredFormat(adapter);
  surface_configuration.usage = WGPUTextureUsage_RenderAttachment;
  surface_configuration.device = device.handle();
  surface_configuration.presentMode = options.present_mode;
  surface_configuration.alphaMode = WGPUCompositeAlphaMode_Opaque;

  return surface_configuration;
}

} // namespace

Application::Console::Console() {
#if defined(_WIN32) && defined(_DEBUG)
  AllocConsole();
  FILE *consoleOut;
  freopen_s(&consoleOut, "conout$", "w", stdout);
#endif
}

Application::Application(const ApplicationOptions &options)
    : instance_(options.instance ? *options.instance : webgpu::InstanceBuilder().Build()),
      adapter_(options.adapter ? options.adapter : ChooseAdapter(instance_.EnumerateAdapters())),
      window_(options.window_title, options.width, options.height),
      surface_(instance_, window_.GetHandle(), window_.GetApplicationInstance()),
      device_(
          webgpu::DeviceBuilder()
              .RegisterDeviceLostCallback(DeviceLost, &error_string_)
              .RegisterUncapturedErrorCallback(UncapturedError, &error_string_)
              .Build(*adapter_)),
      surface_configuration_(
          CreateSurfaceConfiguration(window_, *adapter_, surface_, device_, options)),
      surface_configurator_(surface_, surface_configuration_) {
  ThrowIfError();

  window_.SetOnResize([this](const std::uint32_t width, const std::uint32_t height) {
    surface_configuration_.width = width;
    surface_configuration_.height = height;
    surface_configurator_.Configure(surface_configuration_);
  });

  // adapter no longer needed
  adapter_.reset();
}

void Application::ThrowIfError() {
  if (!error_string_.empty()) {
    throw std::runtime_error(error_string_);
  }
}

bool Application::IsRunning() const {
  return !done_;
}

webgpu::Texture Application::GetCurrentTexture() {
  auto surface_texture = surface_.GetCurrentTexture();

  if (const auto status = surface_texture.status();
      status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal &&
      status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal) {
    surface_configurator_.Configure(surface_configuration_);
  }

  return surface_texture.texture();
}

void Application::PollEvents(
    std::function<void(int key, float mouse_x, float mouse_y)> input_handler) {
  ThrowIfError();

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
  return surface_.Present();
}

webgpu::Device &Application::device() {
  return device_;
}

} // namespace rigel
