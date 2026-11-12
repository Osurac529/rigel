#pragma once

#include <webgpu/wgpu.h>

namespace rigel::graphics {

class RenderPassEncoder {
public:
  explicit RenderPassEncoder(WGPURenderPassEncoder render_pass_encoder);

  RenderPassEncoder(const RenderPassEncoder &);
  RenderPassEncoder &operator=(const RenderPassEncoder &);

  RenderPassEncoder(RenderPassEncoder &&) = default;
  RenderPassEncoder &operator=(RenderPassEncoder &&) = default;

  ~RenderPassEncoder();

  void End() const;

private:
  WGPURenderPassEncoder render_pass_encoder_;
};

} // namespace rigel::graphics
