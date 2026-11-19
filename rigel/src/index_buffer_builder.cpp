#include "rigel/graphics/index_buffer_builder.hpp"

#include "rigel/graphics/exception.hpp"
#include "rigel/mesh/mesh.hpp"

namespace rigel::graphics {

namespace {

std::uint64_t FormatByteSize(const WGPUIndexFormat format) {
  switch (format) {
  case WGPUIndexFormat_Uint16: {
    return 2;
  }

  case WGPUIndexFormat_Uint32: {
    return 4;
  }
  }

  throw Exception("Unknown vertex format.");
}

class Serializer {
public:
  explicit Serializer(std::byte *data_ptr) : data_ptr_(data_ptr) {}

  void operator()(const std::vector<std::uint16_t> &indices) {
    std::memcpy(data_ptr_, indices.data(), indices.size() * sizeof(std::uint16_t));
  }

  void operator()(const std::vector<std::uint32_t> &indices) {
    std::memcpy(data_ptr_, indices.data(), indices.size() * sizeof(std::uint32_t));
  }

private:
  std::byte *data_ptr_;
};

class FormatMapper {
public:
  explicit FormatMapper(WGPUIndexFormat &format) : format_(format) {}

  void operator()(const std::vector<std::uint16_t> &) { format_ = WGPUIndexFormat_Uint16; }

  void operator()(const std::vector<std::uint32_t> &) { format_ = WGPUIndexFormat_Uint32; }

private:
  WGPUIndexFormat &format_;
};

} // namespace

IndexBufferBuilder &IndexBufferBuilder::Add(const mesh::Mesh &mesh) {
  WGPUIndexFormat format = WGPUIndexFormat_Undefined;
  std::visit(FormatMapper(format), mesh.indices());

  if (WGPUIndexFormat_Undefined == format_) {
    format_ = format;
  } else if (format_ != format) {
    throw Exception("Index layouts do not match.");
  }

  const auto begin = buffer_.size();
  buffer_.resize(buffer_.size() + mesh.GetIndexCount() * FormatByteSize(format_));

  std::visit(Serializer(&buffer_[begin]), mesh.indices());

  return *this;
}

IndexBuffer IndexBufferBuilder::Build(webgpu::Device &device) {
  if (buffer_.empty()) {
    throw Exception("Index buffer is empty.");
  }

  IndexBuffer index_buffer;
  index_buffer.buffer =
      webgpu::Buffer(device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index, buffer_.size());
  index_buffer.format = format_;

  device.GetQueue().WriteBuffer(index_buffer.buffer, buffer_.data());

  return index_buffer;
}

} // namespace rigel::graphics
