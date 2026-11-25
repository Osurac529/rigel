#pragma once

#include <cstdint>
#include <unordered_map>
#include <variant>
#include <vector>

#include "rigel/math/math.hpp"
#include "rigel/mesh/attribute.hpp"
#include "rigel/mesh/attribute_id.hpp"

namespace rigel::mesh {

using Indices = std::variant<std::vector<std::uint16_t>, std::vector<std::uint32_t>>;

class Mesh {
public:
  Mesh() = default;

  void Set(AttributeID attribute_id, std::vector<math::vec2f> &&attribute);

  void Set(AttributeID attribute_id, std::uint32_t index, const math::vec2f &attribute);

  //   void AddAttribute(AttributeID attribute_id, const math::vec2f &data);

  template <typename T>
  const T &Get(const AttributeID attribute_id, const std::uint32_t index) const {
    return std::get<std::vector<T>>(attributes_.find(attribute_id)->second)[index];
  }

  void Set(AttributeID attribute_id, std::vector<math::vec3f> &&attribute);

  void Set(AttributeID attribute_id, std::uint32_t index, const math::vec3f &attribute);

  // void AddAttribute(AttributeID attribute_id, const math::vec3f &data);

  void Set(AttributeID attribute_id, std::vector<math::vec4f> &&attribute);

  void Set(AttributeID attribute_id, std::uint32_t index, const math::vec4f &attribute);

  // void AddAttribute(AttributeID attribute_id, const math::vec4f &data);

  const AttributeVector &GetAttribute(AttributeID attribute_id) const;

  void Reserve(const std::unordered_map<AttributeID, Attribute> &attributes, std::size_t size);

  void Resize(const std::unordered_map<AttributeID, Attribute> &attributes, std::size_t size);

  void SetIndices(std::vector<std::uint16_t> &&indices);

  void SetIndices(const std::vector<std::uint16_t> &indices);

  void SetIndices(std::vector<std::uint32_t> &&indices);

  void SetIndices(const std::vector<std::uint32_t> &indices);

  std::vector<AttributeID> GetAttributeIDs() const;

  std::uint32_t GetAttributeCount() const;

  std::uint32_t GetVertexCount() const;

  std::uint32_t GetTriangleCount() const;

  std::uint32_t GetIndexCount() const;

  [[nodiscard]] bool HasAttribute(AttributeID atribute_id) const;

  void VisitTriangleIndices(
      const std::function<void(std::uint32_t, std::uint32_t, std::uint32_t)> &function) const;

  void Validate() const;

  const Indices &indices() const;

private:
  std::unordered_map<AttributeID, AttributeVector> attributes_;
  Indices indices_;
};

} // namespace rigel::mesh
