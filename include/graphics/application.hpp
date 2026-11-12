#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <string>

#include <webgpu/wgpu.h>

#include "graphics/adapter.hpp"
#include "graphics/instance.hpp"

namespace rigel::graphics {

class Window;
class Device;
class Surface;

struct ApplicationOptions {
  std::optional<Instance> instance;

  // When no adapter is provided, one will be chosen automatically.
  std::optional<Adapter> adapter;
  WGPUPresentMode present_mode = WGPUPresentMode_Fifo;
  std::string window_title = "title";
  std::uint32_t width = 1024;
  std::uint32_t height = 768;
};

class Application {
public:
  explicit Application(const ApplicationOptions &options = {});

  void Run(std::function<void(int key, float mouse_x, float mouse_y)> input_handler = {});

private:
  std::unique_ptr<Instance> instance_;
  std::unique_ptr<Device> device_;
  std::unique_ptr<Surface> surface_;
  std::unique_ptr<Window> window_;
  WGPUSurfaceConfiguration surface_configuration_;
  std::function<void(int key, float mouse_x, float mouse_y)> input_handler_;
};

} // namespace rigel::graphics
