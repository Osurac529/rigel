#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include <webgpu/wgpu.h>

#include "graphics/graphics.hpp"

std::size_t ChooseAdapter(const std::vector<rigel::graphics::Adapter> &adapters) {
  std::vector<std::vector<rigel::graphics::Adapter>::const_iterator> adapters_by_type;

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
  std::vector<std::vector<rigel::graphics::Adapter>::const_iterator> adapters_by_type_backend;

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
    throw rigel::graphics::GraphicsException("Could not find an adapter.");
  }

  return std::distance(adapters.begin(), *adapters_by_type_backend.begin());
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

int main() {
  try {
#if defined(_WIN32) && defined(_DEBUG)
    AllocConsole();
    FILE *consoleOut;
    freopen_s(&consoleOut, "conout$", "w", stdout);
#endif

    const std::uint32_t version = wgpuGetVersion();
    const std::uint32_t major = (version >> 24) & 0xFF;
    const std::uint32_t minor = (version >> 16) & 0xFF;
    const std::uint32_t patch = (version >> 8) & 0xFF;
    const std::uint32_t build = version & 0xFF;
    std::cout << major << "." << minor << "." << patch << "." << build << std::endl;

    rigel::graphics::Instance instance;

    auto adapters = instance.EnumerateAdapters();

    for (const auto &adapter : adapters) {
      const auto adapter_info = adapter.GetInfo();

      std::cout << "vendor: " << adapter_info.vendor() << std::endl;
      std::cout << "device: " << adapter_info.device() << std::endl;
      std::cout << "type: " << adapter_info.adapterType() << std::endl;
      std::cout << "backendType: " << adapter_info.backendType() << std::endl;
      std::cout << "description: " << adapter_info.description() << std::endl;
      std::cout << "max buffer size: " << adapter.GetLimits().maxBufferSize << std::endl;

      const auto &features = adapter.GetFeatures();
      std::cout << "features: " << features.size() << std::endl;
      for (const auto &feature : features) {
        std::cout << feature << std::endl;
      }
    }

    WGPUDeviceDescriptor device_descriptor = WGPU_DEVICE_DESCRIPTOR_INIT;
    device_descriptor.deviceLostCallbackInfo.callback = DeviceLost;
    device_descriptor.uncapturedErrorCallbackInfo.callback = UncapturedError;

    const auto chosen_adapter_index = ChooseAdapter(adapters);
    auto device = adapters[chosen_adapter_index].RequestDevice(device_descriptor);
    auto queue = device.GetQueue();

    rigel::graphics::Window window("Rigel", 1024, 768);

    auto surface = instance.CreateSurface(window);

    WGPUSurfaceConfiguration surface_configuration = WGPU_SURFACE_CONFIGURATION_INIT;
    surface_configuration.width = window.GetWidth();
    surface_configuration.height = window.GetHeight();
    surface_configuration.format = surface.GetPreferredFormat(adapters[chosen_adapter_index]);
    surface_configuration.usage = WGPUTextureUsage_RenderAttachment;
    surface_configuration.device = device.native();
    surface_configuration.presentMode = WGPUPresentMode_Fifo;
    surface_configuration.alphaMode = WGPUCompositeAlphaMode_Opaque;

    rigel::graphics::SurfaceConfigurator surface_configurator(surface, surface_configuration);

    adapters.clear();

    window.SetOnResize([&surface_configurator, &surface_configuration](
                           const std::uint32_t width, const std::uint32_t height) {
      surface_configuration.width = width;
      surface_configuration.height = height;
      surface_configurator.Configure(surface_configuration);
    });

#if defined(_WIN32)
    MSG msg;
    auto done(false);

    while (!done) {
      while (::PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (WM_QUIT == msg.message) {
          done = true;
        }

        ::TranslateMessage(&msg);
        ::DispatchMessageW(&msg);
      }

      auto surface_texture = surface.GetCurrentTexture();

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

      rigel::graphics::TextureView texture_view(surface_texture.texture, texture_view_descriptor);

      WGPUCommandEncoderDescriptor command_encoder_descriptor =
          WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT;
      auto command_encoder = device.CreateCommandEncoder(command_encoder_descriptor);

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

      queue.Submit(command_buffer);

      if (WGPUStatus_Success != surface.Present()) {
        std::cout << "failed present" << std::endl;
      }

      wgpuTextureRelease(surface_texture.texture);
    }
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    auto done(false);
    xcb_generic_event_t *event(nullptr);

    while (!done && !idle()) {
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

      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    xcb_disconnect(connection);
#endif

  } catch (const std::exception &exception) {
    std::cout << "Exception: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
