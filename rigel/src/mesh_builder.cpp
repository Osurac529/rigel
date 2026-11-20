#include "rigel/mesh/mesh_builder.hpp"

#include "rigel/mesh/mesh.hpp"

namespace rigel::mesh {

namespace {

class AttributeSetter {
public:
  explicit AttributeSetter(Mesh &mesh) : mesh_(mesh) {}

  void Set(const AttributeID attribute_id, const std::uint32_t index) {
    attribute_id_ = attribute_id;
    index_ = index;
  }

  template <typename T> void operator()(const T &attribute) {
    mesh_.Set(attribute_id_, index_, attribute);
  }

private:
  Mesh &mesh_;
  AttributeID attribute_id_ = 0;
  std::uint32_t index_ = 0;
};

} // namespace

MeshBuilder &MeshBuilder::Add(const Vertex &vertex) {
  const auto iter = vertex_to_index_.try_emplace(vertex, next_index_);

  if (iter.second) {
    indices_.push_back(next_index_);
    ++next_index_;
  } else {
    indices_.push_back(iter.first->second);
  }

  return *this;
}

Mesh MeshBuilder::Build(const Options &options) {
  if (vertex_to_index_.empty()) {
    return {};
  }

  // All vertices should have the same attributes, so get them from the first one.
  Mesh mesh;
  mesh.Resize(vertex_to_index_.begin()->first.attributes(), vertex_to_index_.size());

  AttributeSetter attribute_setter(mesh);

  for (const auto &[vertex, index] : vertex_to_index_) {
    for (const auto &[attribute_id, attribute] : vertex.attributes()) {
      attribute_setter.Set(attribute_id, index);
      std::visit(attribute_setter, attribute);
    }
  }

  if (options.index_mode == IndexMode::FULL) {
    mesh.SetIndices(indices_);
  } else {
    bool can_use_shorts = true;

    for (const auto index : indices_) {
      if (index >= std::numeric_limits<std::uint16_t>::max()) {
        can_use_shorts = false;
        break;
      }
    }

    if (can_use_shorts) {
      std::vector<std::uint16_t> indices;
      indices.reserve(indices_.size());

      for (const auto index : indices_) {
        indices.push_back(static_cast<std::uint16_t>(index));
      }

      mesh.SetIndices(std::move(indices));
    }
  }

  return mesh;
}

} // namespace rigel::mesh
