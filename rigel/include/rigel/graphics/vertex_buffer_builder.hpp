#pragma once

#include <cstdint>
#include <unordered_map>

#include "rigel/mesh/attribute_id.hpp"
#include "webgpu/webgpu.hpp"

namespace rigel {

namespace mesh {

class Mesh;

} // namespace mesh

namespace graphics {

struct VertexBuffer {
  webgpu::VertexBufferLayout layout;
  webgpu::Buffer buffer;
};

class VertexBufferBuilder {
public:
  struct Options {
    bool half_float = false;
    bool instanced = false;
  };

  // An empty attribute_id_to_location means the attribute id and locations are the same.
  explicit VertexBufferBuilder(const Options &options = {});

  explicit VertexBufferBuilder(
      const std::unordered_map<mesh::AttributeID, std::uint32_t> &attribute_id_to_location,
      const Options &options = {});

  VertexBufferBuilder(const VertexBufferBuilder &) = delete;
  VertexBufferBuilder &operator=(const VertexBufferBuilder &) = delete;

  VertexBufferBuilder(VertexBufferBuilder &&) = default;
  VertexBufferBuilder &operator=(VertexBufferBuilder &&) = default;

  ~VertexBufferBuilder() = default;

  VertexBufferBuilder &Add(const mesh::Mesh &mesh);

  VertexBuffer Build(webgpu::Device &device);

private:
  std::unordered_map<mesh::AttributeID, std::uint32_t> attribute_id_to_location_;
  std::unordered_map<mesh::AttributeID, WGPUVertexFormat> attribute_id_to_format_;
  webgpu::VertexBufferLayout layout_;
  std::vector<std::byte> buffer_;
  Options options_;
  std::uint64_t stride_ = 0;
};

} // namespace graphics

} // namespace rigel
