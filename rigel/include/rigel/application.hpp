#pragma once

#include <functional>
#include <memory>
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

  bool IsRunning() const;

  void PollEvents(std::function<void(int key, float mouse_x, float mouse_y)> input_handler = {});

  webgpu::Texture GetCurrentTexture();

  WGPUStatus Present();

  webgpu::Device &device();

private:
  void ThrowIfError();

  bool done_ = false;
  // todo: see if there is a way to do this without all the unique_ptr's
  std::unique_ptr<webgpu::Instance> instance_;
  std::unique_ptr<webgpu::Device> device_;
  std::unique_ptr<webgpu::Surface> surface_;
  std::unique_ptr<Window> window_;
  std::unique_ptr<webgpu::SurfaceConfigurator> surface_configurator_;
  WGPUSurfaceConfiguration surface_configuration_;
  std::function<void(int key, float mouse_x, float mouse_y)> input_handler_;
  std::string error_string_;
};

} // namespace rigel
