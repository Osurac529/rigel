#include "graphics/render_pass_encoder.hpp"

namespace rigel::graphics {

void RenderPassEncoder::End() const {
  wgpuRenderPassEncoderEnd(native());
}

} // namespace rigel::graphics
