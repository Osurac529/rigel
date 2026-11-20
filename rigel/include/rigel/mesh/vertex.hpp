#pragma once

#include <functional>
#include <unordered_map>
#include <variant>

#include "rigel/math/math.hpp"
#include "rigel/mesh/attribute.hpp"
#include "rigel/mesh/attribute_id.hpp"

namespace rigel::mesh {

class Vertex {
public:
  void Set(const AttributeID attribute_id, const math::vec2f &attribute);

  void Set(const AttributeID attribute_id, const math::vec3f &attribute);

  void Set(const AttributeID attribute_id, const math::vec4f &attribute);

  std::vector<AttributeID> GetAttributeIDs() const;

  std::size_t hash() const;

  const std::unordered_map<AttributeID, Attribute> &attributes() const;

  bool operator==(const Vertex &vertex) const;

private:
  mutable std::size_t hash_ = 0;
  std::unordered_map<AttributeID, Attribute> attributes_;
};

} // namespace rigel::mesh

namespace std {
template <> struct hash<rigel::mesh::Vertex> {
  std::size_t operator()(const rigel::mesh::Vertex &vertex) const noexcept { return vertex.hash(); }
};

} // namespace std
