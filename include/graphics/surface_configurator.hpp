#pragma once

#include <webgpu/wgpu.h>

#include "graphics/surface.hpp"
#include "utilities/move_only.hpp"

namespace rigel::graphics {

class SurfaceConfigurator : private utilities::MoveOnly {
public:
  explicit SurfaceConfigurator(
      const Surface &surface,
      const WGPUSurfaceConfiguration &configuration);

  ~SurfaceConfigurator();

private:
  Surface surface_;
};

} // namespace rigel::graphics
