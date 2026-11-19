#include "rigel/graphics/vertex_buffer_builder.hpp"

#include "rigel/graphics/exception.hpp"
#include "rigel/mesh/mesh.hpp"

namespace rigel::graphics {

namespace {

std::uint64_t FormatByteSize(const WGPUVertexFormat format) {
  switch (format) {
  case WGPUVertexFormat_Float16x2: {
    return 4;
  }

  case WGPUVertexFormat_Float32x2:
  case WGPUVertexFormat_Float16x4: {
    return 8;
  }

  case WGPUVertexFormat_Float32x3: {
    return 12;
  }

  case WGPUVertexFormat_Float32x4: {
    return 16;
  }
  }

  throw Exception("Unknown vertex format.");
}

class Serializer {
public:
  explicit Serializer(std::byte *&data_ptr, const std::uint32_t index)
      : data_ptr_(data_ptr), index_(index) {}

  template <typename T> void operator()(const std::vector<T> &attribute) {
    const auto size = sizeof(T);
    std::memcpy(data_ptr_, &attribute[index_], size);
    data_ptr_ += size;
  }

private:
  std::byte *&data_ptr_;
  std::uint32_t index_;
};

class FormatMapper {
public:
  explicit FormatMapper(WGPUVertexFormat &format, const bool half_float)
      : format_(format), half_float_(half_float) {}

  void operator()(const std::vector<math::vec2f> &) {
    format_ = half_float_ ? WGPUVertexFormat_Float16x2 : WGPUVertexFormat_Float32x2;
  }

  void operator()(const std::vector<math::vec3f> &) {
    // there is no 3 component format for half float
    format_ = half_float_ ? WGPUVertexFormat_Float16x4 : WGPUVertexFormat_Float32x3;
  }

  void operator()(const std::vector<math::vec4f> &) {
    format_ = half_float_ ? WGPUVertexFormat_Float16x4 : WGPUVertexFormat_Float32x4;
  }

private:
  WGPUVertexFormat &format_;
  bool half_float_;
};

std::unordered_map<mesh::AttributeID, WGPUVertexFormat>
BuildAttributeIdToFormat(const mesh::Mesh &mesh, const bool half_float) {
  std::unordered_map<mesh::AttributeID, WGPUVertexFormat> attribute_id_to_format;

  for (const auto attribute_id : mesh.GetAttributeIDs()) {
    WGPUVertexFormat format;
    std::visit(FormatMapper(format, half_float), mesh.GetAttribute(attribute_id));
    attribute_id_to_format.try_emplace(attribute_id, format);
  }

  return attribute_id_to_format;
}

} // namespace

VertexBufferBuilder::VertexBufferBuilder(const Options &options) : options_(options) {}

VertexBufferBuilder::VertexBufferBuilder(
    const std::unordered_map<mesh::AttributeID, std::uint32_t> &attribute_id_to_location,
    const Options &options)
    : attribute_id_to_location_(attribute_id_to_location), options_(options) {}

VertexBufferBuilder &VertexBufferBuilder::Add(const mesh::Mesh &mesh) {
  auto attribute_id_to_format = BuildAttributeIdToFormat(mesh, options_.half_float);

  if (attribute_id_to_format_.empty()) {
    webgpu::VertexBufferLayoutBuilder builder;

    for (const auto &[attribute_id, format] : attribute_id_to_format) {
      std::uint32_t shader_location = 0;

      if (attribute_id_to_location_.empty()) {
        shader_location = attribute_id;
      } else if (
          const auto iter = attribute_id_to_location_.find(attribute_id);
          attribute_id_to_location_.end() != iter) {
        shader_location = iter->second;
      } else {
        continue;
      }

      builder.AddAttribute(format, stride_, shader_location);

      // todo: need to handle alignment
      stride_ += FormatByteSize(format);
    }

    layout_ = builder.SetStride(stride_)
                  .SetStepMode(
                      options_.instanced ? WGPUVertexStepMode_Instance : WGPUVertexStepMode_Vertex)
                  .Build();

    attribute_id_to_format_ = std::move(attribute_id_to_format);
  } else if (attribute_id_to_format_ != attribute_id_to_format) {
    throw Exception("Vertex layouts do not match.");
  }

  const auto vertex_count = mesh.GetVertexCount();
  const auto begin = buffer_.size();
  buffer_.resize(buffer_.size() + vertex_count * stride_);
  auto *data_ptr = &buffer_[begin];

  // todo: this might able to be done faster
  for (std::uint32_t index = 0; index < vertex_count; ++index) {
    for (const auto attribute_id : mesh.GetAttributeIDs()) {
      std::visit(Serializer(data_ptr, index), mesh.GetAttribute(attribute_id));
    }
  }

  return *this;
}

VertexBuffer VertexBufferBuilder::Build(webgpu::Device &device) {
  if (buffer_.empty()) {
    throw Exception("Vertex buffer is empty.");
  }

  VertexBuffer vertex_buffer;
  vertex_buffer.buffer =
      webgpu::Buffer(device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex, buffer_.size());
  vertex_buffer.layout = layout_;

  device.GetQueue().WriteBuffer(vertex_buffer.buffer, buffer_.data());

  return vertex_buffer;
}

} // namespace rigel::graphics
