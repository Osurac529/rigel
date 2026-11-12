#include "graphics/surface_configurator.hpp"

namespace rigel::graphics {

SurfaceConfigurator::SurfaceConfigurator(
    const Surface &surface,
    const WGPUSurfaceConfiguration &configuration)
    : surface_(surface) {
  Configure(configuration);
}

SurfaceConfigurator::~SurfaceConfigurator() {
  wgpuSurfaceUnconfigure(surface_.native());
}

void SurfaceConfigurator::Configure(const WGPUSurfaceConfiguration &configuration) {
  wgpuSurfaceConfigure(surface_.native(), &configuration);
}

} // namespace rigel::graphics
