#pragma once

#include <webgpu/wgpu.h>

#include "webgpu/surface.hpp"

namespace webgpu {

class SurfaceConfigurator {
public:
  explicit SurfaceConfigurator(
      const Surface &surface,
      const WGPUSurfaceConfiguration &configuration = WGPU_SURFACE_CONFIGURATION_INIT);

  SurfaceConfigurator(const SurfaceConfigurator &) = default;
  SurfaceConfigurator &operator=(const SurfaceConfigurator &) = default;

  SurfaceConfigurator(SurfaceConfigurator &&) = default;
  SurfaceConfigurator &operator=(SurfaceConfigurator &&) = default;

  ~SurfaceConfigurator();

  void Configure(const WGPUSurfaceConfiguration &configuration = WGPU_SURFACE_CONFIGURATION_INIT);

private:
  Surface surface_;
};

} // namespace webgpu
