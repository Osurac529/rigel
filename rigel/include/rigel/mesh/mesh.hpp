#pragma once

#include <cstdint>
#include <unordered_map>
#include <variant>
#include <vector>

#include "rigel/math/math.hpp"
#include "rigel/mesh/attribute_id.hpp"

namespace rigel::mesh {

class Mesh {
public:
  using Attribute =
      std::variant<std::vector<math::vec2f>, std::vector<math::vec3f>, std::vector<math::vec4f>>;

  using Indices = std::variant<std::vector<std::uint16_t>, std::vector<std::uint32_t>>;

  Mesh() = default;

  explicit Mesh(std::vector<math::vec3f> &&positions, std::vector<std::uint16_t> &&indices);

  explicit Mesh(std::vector<math::vec3f> &&positions, std::vector<std::uint32_t> &&indices);

  // void SetAttribute(AttributeID attribute_id, std::vector<math::vec2f> &&data);

  // void SetAttribute(AttributeID attribute_id, std::uint32_t index, const math::vec2f &data);

  // void AddAttribute(AttributeID attribute_id, const math::vec2f &data);

  // void SetAttribute(AttributeID attribute_id, std::vector<math::vec3f> &&data);

  // void SetAttribute(AttributeID attribute_id, std::uint32_t index, const math::vec3f &data);

  // void AddAttribute(AttributeID attribute_id, const math::vec3f &data);

  // void SetAttribute(AttributeID attribute_id, std::vector<math::vec4f> &&data);

  // void SetAttribute(AttributeID attribute_id, std::uint32_t index, const math::vec4f &data);

  // void AddAttribute(AttributeID attribute_id, const math::vec4f &data);

  const Attribute &GetAttribute(AttributeID attribute_id) const;

  // void SetIndices(std::vector<std::uint16_t> &&indices);

  // void SetIndices(std::vector<std::uint32_t> &&indices);

  std::vector<AttributeID> GetAttributeIDs() const;

  std::uint32_t GetAttributeCount() const;

  std::uint32_t GetVertexCount() const;

  std::uint32_t GetTriangleCount() const;

  std::uint32_t GetIndexCount() const;

  void Validate() const;

  const Indices &indices() const;

private:
  std::unordered_map<AttributeID, Attribute> attributes_;
  Indices indices_;
};

} // namespace rigel::mesh
