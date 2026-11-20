#include "rigel/mesh/mesh.hpp"

#include <unordered_set>

#include "rigel/mesh/exception.hpp"

namespace rigel::mesh {

namespace {

class SizeVisitor {
public:
  template <typename T> void operator()(const std::vector<T> &attribute) {
    size_ = static_cast<std::uint32_t>(attribute.size());
  }

  std::uint32_t size() const { return size_; }

private:
  std::uint32_t size_ = 0;
};

std::uint32_t GetSize(const AttributeVector &attribute) {
  SizeVisitor size_visitor;
  std::visit(size_visitor, attribute);

  return size_visitor.size();
}

std::uint32_t GetSize(const Indices &indices) {
  SizeVisitor size_visitor;
  std::visit(size_visitor, indices);

  return size_visitor.size();
}

class IndicesValidator {
public:
  explicit IndicesValidator(const std::uint32_t vertex_count) : vertex_count_(vertex_count) {}

  template <typename T> void operator()(const std::vector<T> &indices) const {
    for (const auto index : indices) {
      if (index >= vertex_count_) {
        throw Exception("Index out of bounds.");
      }
    }

    for (std::size_t i = 0; i < indices.size(); i += 3) {
      if (indices[i] == indices[i + 1] || indices[i] == indices[i + 2] ||
          indices[i + 1] == indices[i + 2]) {
        throw Exception("Degenerate by indices.");
      }
    }
  }

private:
  std::uint32_t vertex_count_;
};

void ValidateIndices(const Indices &indices, const std::uint32_t vertex_count) {
  std::visit(IndicesValidator(vertex_count), indices);
}

class Reserver {
public:
  explicit Reserver(
      const AttributeID attribute_id,
      std::unordered_map<AttributeID, AttributeVector> &attributes,
      const std::size_t size)
      : attribute_id_(attribute_id), attributes_(attributes), size_(size) {}

  template <typename T> void operator()(const T &) {
    std::get<std::vector<T>>(attributes_[attribute_id_]).reserve(size_);
  }

private:
  AttributeID attribute_id_;
  std::unordered_map<AttributeID, AttributeVector> &attributes_;
  std::size_t size_;
};

class Resizer {
public:
  explicit Resizer(
      const AttributeID attribute_id,
      std::unordered_map<AttributeID, AttributeVector> &attributes,
      const std::size_t size)
      : attribute_id_(attribute_id), attributes_(attributes), size_(size) {}

  template <typename T> void operator()(const T &) {
    if (!attributes_.contains(attribute_id_)) {
      attributes_[attribute_id_] = std::vector<T>(size_);

      return;
    }

    std::get<std::vector<T>>(attributes_[attribute_id_]).resize(size_);
  }

private:
  AttributeID attribute_id_;
  std::unordered_map<AttributeID, AttributeVector> &attributes_;
  std::size_t size_;
};

} // namespace

void Mesh::Set(const AttributeID attribute_id, std::vector<math::vec2f> &&attribute) {
  attributes_[attribute_id] = std::move(attribute);
}

void Mesh::Set(
    const AttributeID attribute_id,
    const std::uint32_t index,
    const math::vec2f &attribute) {
  auto &buffer = std::get<std::vector<math::vec2f>>(attributes_[attribute_id]);

  if (buffer.size() <= index) {
    buffer.resize(index + 1);
  }

  buffer[index] = attribute;
}

void Mesh::Set(const AttributeID attribute_id, std::vector<math::vec3f> &&attribute) {
  attributes_[attribute_id] = std::move(attribute);
}

void Mesh::Set(
    const AttributeID attribute_id,
    const std::uint32_t index,
    const math::vec3f &attribute) {
  auto &buffer = std::get<std::vector<math::vec3f>>(attributes_[attribute_id]);

  if (buffer.size() <= index) {
    buffer.resize(index + 1);
  }

  buffer[index] = attribute;
}

void Mesh::Set(const AttributeID attribute_id, std::vector<math::vec4f> &&attribute) {
  attributes_[attribute_id] = std::move(attribute);
}

void Mesh::Set(
    const AttributeID attribute_id,
    const std::uint32_t index,
    const math::vec4f &attribute) {
  auto &buffer = std::get<std::vector<math::vec4f>>(attributes_[attribute_id]);

  if (buffer.size() <= index) {
    buffer.resize(index + 1);
  }

  buffer[index] = attribute;
}

void Mesh::Reserve(
    const std::unordered_map<AttributeID, Attribute> &attributes,
    const std::size_t size) {
  for (const auto &[attribute_id, attribute] : attributes) {
    std::visit(Reserver(attribute_id, attributes_, size), attribute);
  }
}

void Mesh::Resize(
    const std::unordered_map<AttributeID, Attribute> &attributes,
    const std::size_t size) {
  for (const auto &[attribute_id, attribute] : attributes) {
    std::visit(Resizer(attribute_id, attributes_, size), attribute);
  }
}

void Mesh::SetIndices(std::vector<std::uint16_t> &&indices) {
  indices_ = std::move(indices);
}

void Mesh::SetIndices(const std::vector<std::uint16_t> &indices) {
  indices_ = indices;
}

void Mesh::SetIndices(std::vector<std::uint32_t> &&indices) {
  indices_ = std::move(indices);
}

void Mesh::SetIndices(const std::vector<std::uint32_t> &indices) {
  indices_ = indices;
}

const AttributeVector &Mesh::GetAttribute(const AttributeID attribute_id) const {
  return attributes_.at(attribute_id);
}

std::vector<AttributeID> Mesh::GetAttributeIDs() const {
  std::vector<AttributeID> attribute_ids;
  attribute_ids.reserve(attributes_.size());

  for (const auto &[attribute_id, ignore] : attributes_) {
    attribute_ids.push_back(attribute_id);
  }

  return attribute_ids;
}

std::uint32_t Mesh::GetVertexCount() const {
  if (!attributes_.empty()) {
    return GetSize(attributes_.begin()->second);
  }

  return 0;
}

std::uint32_t Mesh::GetAttributeCount() const {
  return static_cast<std::uint32_t>(attributes_.size());
}

std::uint32_t Mesh::GetTriangleCount() const {
  return GetIndexCount() / 3;
}

std::uint32_t Mesh::GetIndexCount() const {
  return GetSize(indices_);
}

void Mesh::Validate() const {
  if (attributes_.empty()) {
    throw Exception("Attributes are missing.");
  }

  // empty indices could be allowed for non indexed meshes
  if (0 != GetIndexCount() % 3) {
    throw Exception("Indices size is not a multiple of three.");
  }

  ValidateIndices(indices_, GetVertexCount());

  std::unordered_set<std::uint32_t> sizes;

  for (const auto &[ignore, attribute] : attributes_) {
    sizes.emplace(GetSize(attribute));
  }

  if (1 != sizes.size()) {
    throw Exception("Attribute sizes mismatch, at least one attribute is a different size.");
  }

  if (0 == *sizes.begin()) {
    throw Exception("Attributes are empty.");
  }
}

const Indices &Mesh::indices() const {
  return indices_;
}

} // namespace rigel::mesh
