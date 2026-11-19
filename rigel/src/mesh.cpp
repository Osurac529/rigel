#include "rigel/mesh/mesh.hpp"

#include <unordered_set>

#include "rigel/mesh/exception.hpp"

namespace rigel::mesh {

namespace {

class SizeVisitor {
public:
  explicit SizeVisitor(std::uint32_t &size) : size_(size) {}

  template <typename T> void operator()(const std::vector<T> &attribute) {
    size_ = static_cast<std::uint32_t>(attribute.size());
  }

private:
  std::uint32_t& size_;
};

std::uint32_t GetSize(
    const std::variant<std::vector<math::vec2f>, std::vector<math::vec3f>, std::vector<math::vec4f>>
        &attribute) {
  std::uint32_t size = 0;
  std::visit(SizeVisitor(size), attribute);

  return size;
}

std::uint32_t
GetSize(const std::variant<std::vector<std::uint16_t>, std::vector<std::uint32_t>> &indices) {
  std::uint32_t size = 0;
  std::visit(SizeVisitor(size), indices);

  return size;
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

// todo: move the Attribute/Indices using out of the Mesh class
void ValidateIndices(
    const std::variant<std::vector<std::uint16_t>, std::vector<std::uint32_t>> &indices,
    const std::uint32_t vertex_count) {
  std::visit(IndicesValidator(vertex_count), indices);
}

} // namespace

Mesh::Mesh(std::vector<math::vec3f> &&positions, std::vector<std::uint16_t> &&indices)
    : indices_(std::move(indices)) {
  attributes_.try_emplace(POSITION_ATTRIBUTE, std::move(positions));
}

Mesh::Mesh(std::vector<math::vec3f> &&positions, std::vector<std::uint32_t> &&indices)
    : indices_(std::move(indices)) {
  attributes_.try_emplace(POSITION_ATTRIBUTE, std::move(positions));
}

const Mesh::Attribute &Mesh::GetAttribute(AttributeID attribute_id) const {
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

const Mesh::Indices &Mesh::indices() const {
  return indices_;
}

} // namespace rigel::mesh
