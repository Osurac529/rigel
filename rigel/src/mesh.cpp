#include "rigel/mesh/mesh.hpp"

#include "rigel/mesh/exception.hpp"

namespace rigel::mesh {

Mesh::Mesh(std::vector<math::vec3f> &&positions, std::vector<std::uint16_t> &&indices)
    : positions_(std::move(positions)), indices_(std::move(indices)) {}

std::uint32_t Mesh::GetVertexCount() const {
  return static_cast<std::uint32_t>(positions_.size());
}

std::uint32_t Mesh::GetTriangleCount() const {
  return static_cast<std::uint32_t>(indices_.size() / 3);
}

void Mesh::Validate() const {
  if (positions_.empty()) {
    throw Exception("Positions are missing.");
  }

  if (0 != indices_.size() % 3) {
    throw Exception("Indices size is not a multiple of three.");
  }

  for (const auto index : indices_) {
    if (index >= positions_.size()) {
      throw Exception("Index out of bounds.");
    }
  }

  for (std::size_t i = 0; i < indices_.size(); i += 3) {
    if (indices_[i] == indices_[i + 1] || indices_[i] == indices_[i + 2] ||
        indices_[i + 1] == indices_[i + 2]) {
      throw Exception("Degenerate by indices.");
    }
  }
}

const std::vector<math::vec3f> &Mesh::positions() const {
  return positions_;
}

const std::vector<std::uint16_t> &Mesh::indices() const {
  return indices_;
}

} // namespace rigel::mesh
