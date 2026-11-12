#include "graphics/surface_configurator.hpp"

namespace rigel::graphics {

SurfaceConfigurator::SurfaceConfigurator(
    const Surface &surface,
    const WGPUSurfaceConfiguration &configuration)
    : surface_(surface) {
  wgpuSurfaceConfigure(surface_.native(), &configuration);
}

SurfaceConfigurator::~SurfaceConfigurator() {
  wgpuSurfaceUnconfigure(surface_.native());
}

} // namespace rigel::graphics
