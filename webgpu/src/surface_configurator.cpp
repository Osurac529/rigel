#include "webgpu/surface_configurator.hpp"

namespace webgpu {

SurfaceConfigurator::SurfaceConfigurator(
    const Surface &surface,
    const WGPUSurfaceConfiguration &configuration)
    : surface_(surface) {
  Configure(configuration);
}

SurfaceConfigurator::~SurfaceConfigurator() {
  wgpuSurfaceUnconfigure(surface_.handle());
}

void SurfaceConfigurator::Configure(const WGPUSurfaceConfiguration &configuration) {
  wgpuSurfaceConfigure(surface_.handle(), &configuration);
}

} // namespace webgpu
