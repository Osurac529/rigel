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
#include "graphics/texture_view.hpp"
#include "graphics/window.hpp"

namespace rigel::graphics {

namespace {

Adapter ChooseAdapter(const std::vector<Adapter> &adapters) {
  std::vector<std::vector<Adapter>::const_iterator> adapters_by_type;

  // look for discrete
  for (auto iter = adapters.begin(); adapters.end() != iter; ++iter) {
    if (WGPUAdapterType_DiscreteGPU == iter->GetInfo().adapterType()) {
      adapters_by_type.emplace_back(iter);
    }
  }

  if (adapters_by_type.empty()) {
    // look for integrated
    for (auto iter = adapters.begin(); adapters.end() != iter; ++iter) {
      if (WGPUAdapterType_IntegratedGPU == iter->GetInfo().adapterType()) {
        adapters_by_type.emplace_back(iter);
      }
    }
  }

  if (adapters_by_type.empty()) {
    // look for CPU
    for (auto iter = adapters.begin(); adapters.end() != iter; ++iter) {
      if (WGPUAdapterType_CPU == iter->GetInfo().adapterType()) {
        adapters_by_type.emplace_back(iter);
      }
    }
  }

  // look for vulkan
  std::vector<std::vector<Adapter>::const_iterator> adapters_by_type_backend;

  for (auto iter = adapters_by_type.begin(); adapters_by_type.end() != iter; ++iter) {
    if (WGPUBackendType_Vulkan == (*iter)->GetInfo().backendType()) {
      adapters_by_type_backend.emplace_back(*iter);
    }
  }

  if (adapters_by_type_backend.empty()) {
    // look for platform specific backends
    for (auto iter = adapters_by_type.begin(); adapters_by_type.end() != iter; ++iter) {
#if defined(_WIN32)
      if (WGPUBackendType_D3D12 == (*iter)->GetInfo().backendType()) {
        adapters_by_type_backend.emplace_back(*iter);
      }
#elif defined(__linux__) && !defined(__ANDROID__)
      if (WGPUBackendType_OpenGL == (*iter)->GetInfo().backendType()) {
        adapters_by_type_backend.emplace_back(*iter);
      }
#elif defined(__APPLE__)
      if (WGPUBackendType_Metal == (*iter)->GetInfo().backendType()) {
        adapters_by_type_backend.emplace_back(*iter);
      }
#elif defined(__linux__) && defined(__ANDROID__)
      if (WGPUBackendType_OpenGLES == (*iter)->GetInfo().backendType()) {
        adapters_by_type_backend.emplace_back(*iter);
      }
#endif
    }
  }

  if (adapters_by_type_backend.empty()) {
    // look for lesser platform specific backends
    for (auto iter = adapters_by_type.begin(); adapters_by_type.end() != iter; ++iter) {
#if defined(_WIN32)
      if (WGPUBackendType_D3D11 == (*iter)->GetInfo().backendType()) {
        adapters_by_type_backend.emplace_back(*iter);
      }
#elif defined(__linux__) && !defined(__ANDROID__)
      if (WGPUBackendType_OpenGLES == (*iter)->GetInfo().backendType()) {
        adapters_by_type_backend.emplace_back(*iter);
      }
#elif defined(__APPLE__)
      if (WGPUBackendType_OpenGL == (*iter)->GetInfo().backendType()) {
        adapters_by_type_backend.emplace_back(*iter);
      }
#endif
    }
  }

  if (adapters_by_type_backend.empty()) {
    // look for lesser platform specific backends
    for (auto iter = adapters_by_type.begin(); adapters_by_type.end() != iter; ++iter) {
#if defined(_WIN32)
      if (WGPUBackendType_OpenGL == (*iter)->GetInfo().backendType()) {
        adapters_by_type_backend.emplace_back(*iter);
      }
#endif
    }
  }

  if (adapters_by_type_backend.empty()) {
    throw GraphicsException("Could not find an adapter.");
  }

  return **adapters_by_type_backend.begin();
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

  std::cout << "uncaptured error: " << type << std::endl;

  if (message.data) {
    std::cout << std::string_view(message.data, message.length) << std::endl;
  }
}

} // namespace

Application::Application(const ApplicationOptions &options) {
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

  surface_configuration_ = WGPU_SURFACE_CONFIGURATION_INIT;
  surface_configuration_.width = window_->GetWidth();
  surface_configuration_.height = window_->GetHeight();
  surface_configuration_.format = surface_->GetPreferredFormat(*adapter);
  surface_configuration_.usage = WGPUTextureUsage_RenderAttachment;
  surface_configuration_.device = device_->native();
  surface_configuration_.presentMode = options.present_mode;
  surface_configuration_.alphaMode = WGPUCompositeAlphaMode_Opaque;
}

void Application::Run(std::function<void(int key, float mouse_x, float mouse_y)> input_handler) {
  SurfaceConfigurator surface_configurator(*surface_, surface_configuration_);

  window_->SetOnResize(
      [this, &surface_configurator](const std::uint32_t width, const std::uint32_t height) {
        surface_configuration_.width = width;
        surface_configuration_.height = height;
        surface_configurator.Configure(surface_configuration_);
      });

  bool done = false;

#if defined(_WIN32)
  MSG msg;
#elif defined(__linux__)
  xcb_generic_event_t *event = nullptr;
#endif

  while (!done) {
#if defined(_WIN32)
    while (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
      if (WM_QUIT == msg.message) {
        done = true;
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

    auto surface_texture = surface_->GetCurrentTexture();

    if (surface_texture.status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal &&
        surface_texture.status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal) {
      std::cout << "needs reconfigure" << std::endl;
      continue;
    }

    WGPUTextureViewDescriptor texture_view_descriptor = WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT;
    texture_view_descriptor.format = wgpuTextureGetFormat(surface_texture.texture);
    texture_view_descriptor.dimension = WGPUTextureViewDimension_2D;
    texture_view_descriptor.baseMipLevel = 0;
    texture_view_descriptor.mipLevelCount = 1;
    texture_view_descriptor.baseArrayLayer = 0;
    texture_view_descriptor.arrayLayerCount = 1;
    texture_view_descriptor.aspect = WGPUTextureAspect_All;

    TextureView texture_view(surface_texture.texture, texture_view_descriptor);

    WGPUCommandEncoderDescriptor command_encoder_descriptor = WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT;
    auto command_encoder = device_->CreateCommandEncoder(command_encoder_descriptor);

    WGPURenderPassColorAttachment render_pass_color_attachment =
        WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
    render_pass_color_attachment.view = texture_view.native();
    render_pass_color_attachment.loadOp = WGPULoadOp_Clear;
    render_pass_color_attachment.storeOp = WGPUStoreOp_Store;
    render_pass_color_attachment.clearValue = WGPUColor{1.0, 0.0, 0.0, 1.0};

    WGPURenderPassDescriptor render_pass_descriptor = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
    render_pass_descriptor.colorAttachmentCount = 1;
    render_pass_descriptor.colorAttachments = &render_pass_color_attachment;

    auto render_pass = command_encoder.BeginRenderPass(render_pass_descriptor);
    render_pass.End();

    auto command_buffer = command_encoder.Finish();

    device_->GetQueue().Submit(command_buffer);

    if (WGPUStatus_Success != surface_->Present()) {
      std::cout << "failed present" << std::endl;
    }

    wgpuTextureRelease(surface_texture.texture);
  }

#if defined(__linux__)
  xcb_disconnect(connection);
#endif
}

} // namespace rigel::graphics
