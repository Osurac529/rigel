#include "graphics/render_pass_encoder.hpp"

#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

RenderPassEncoder::RenderPassEncoder(WGPURenderPassEncoder render_pass_encoder)
    : render_pass_encoder_(render_pass_encoder) {
  if (!render_pass_encoder_) {
    throw GraphicsException("");
  }
}

RenderPassEncoder::RenderPassEncoder(const RenderPassEncoder &other)
    : render_pass_encoder_(other.render_pass_encoder_) {
  wgpuRenderPassEncoderAddRef(render_pass_encoder_);
}

RenderPassEncoder &RenderPassEncoder::operator=(const RenderPassEncoder &other) {
  if (this != &other) {
    render_pass_encoder_ = other.render_pass_encoder_;
    wgpuRenderPassEncoderAddRef(render_pass_encoder_);
  }

  return *this;
}

RenderPassEncoder::~RenderPassEncoder() {
  wgpuRenderPassEncoderRelease(render_pass_encoder_);
}

void RenderPassEncoder::End() const {
  wgpuRenderPassEncoderEnd(render_pass_encoder_);
}

} // namespace rigel::graphics
