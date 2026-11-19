#pragma once

#include <vector>

#include "webgpu/webgpu.hpp"

namespace rigel {

namespace mesh {

class Mesh;

}

namespace graphics {

struct IndexBuffer {
  WGPUIndexFormat format;
  webgpu::Buffer buffer;
};

class IndexBufferBuilder {
public:
  IndexBufferBuilder &Add(const mesh::Mesh &mesh);

  IndexBuffer Build(webgpu::Device &device);

private:
  WGPUIndexFormat format_ = WGPUIndexFormat_Undefined;
  std::vector<std::byte> buffer_;
};

} // namespace graphics

} // namespace rigel
