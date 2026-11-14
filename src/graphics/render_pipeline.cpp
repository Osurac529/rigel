#include "graphics/render_pipeline.hpp"

#include "graphics/device.hpp"

namespace rigel::graphics {

RenderPipeline::RenderPipeline(Device &device, const WGPURenderPipelineDescriptor &descriptor)
    : RenderPipeline(wgpuDeviceCreateRenderPipeline(device.native(), &descriptor)) {}

} // namespace rigel::graphics
