#pragma once

#include <functional>
#include <optional>
#include <string>

#include "rigel/window.hpp"
#include "webgpu/webgpu.hpp"

namespace rigel {

struct ApplicationOptions {
  std::optional<webgpu::Instance> instance;

  // When no adapter is provided, one will be chosen automatically.
  std::optional<webgpu::Adapter> adapter;
  WGPUPresentMode present_mode = WGPUPresentMode_Fifo;
  std::string window_title = "title";
  std::uint32_t width = 1024;
  std::uint32_t height = 768;
};

class Application {
public:
  explicit Application(const ApplicationOptions &options = {});

  Application(const Application &) = delete;
  Application &operator=(const Application &) = delete;
  Application(Application &&) = delete;
  Application &operator=(Application &&) = delete;

  ~Application() = default;

  bool IsRunning() const;

  void PollEvents(std::function<void(int key, float mouse_x, float mouse_y)> input_handler = {});

  webgpu::Texture GetCurrentTexture();

  WGPUStatus Present();

  webgpu::Device &device();

private:
  struct Console {
    Console();
  };

  bool done_ = false;
  Console console_;
  webgpu::Instance instance_;
  std::optional<webgpu::Adapter> adapter_;
  Window window_;
  webgpu::Surface surface_;
  webgpu::Device device_;
  WGPUSurfaceConfiguration surface_configuration_;
  webgpu::SurfaceConfigurator surface_configurator_;
  std::function<void(int key, float mouse_x, float mouse_y)> input_handler_;
};

} // namespace rigel
