#pragma once

#include <webgpu/wgpu.h>

#include "graphics/surface.hpp"

namespace rigel::graphics {

class SurfaceConfigurator {
public:
  explicit SurfaceConfigurator(
      const Surface &surface,
      const WGPUSurfaceConfiguration &configuration = WGPU_SURFACE_CONFIGURATION_INIT);

  ~SurfaceConfigurator();

  void Configure(const WGPUSurfaceConfiguration &configuration = WGPU_SURFACE_CONFIGURATION_INIT);

private:
  Surface surface_;
};

} // namespace rigel::graphics
