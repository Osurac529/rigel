#pragma once

#include <cstdint>
#include <vector>

#include "rigel/math/vec3.hpp"

namespace rigel::mesh {

constexpr inline std::uint32_t POSITION_ATTRIBUTE = 0;
constexpr inline std::uint32_t TEXTURE_ATTRIBUTE = 1;
constexpr inline std::uint32_t NORMAL_ATTRIBUTE = 1;

class Mesh {
public:
  explicit Mesh(std::vector<math::vec3f> &&positions, std::vector<std::uint16_t> &&indices);

  std::uint32_t GetVertexCount() const;

  std::uint32_t GetTriangleCount() const;

  void Validate() const;

  const std::vector<math::vec3f> &positions() const;

  const std::vector<std::uint16_t> &indices() const;

private:
  bool use_short_indices_ = false;
  std::vector<math::vec3f> positions_;
  std::vector<std::uint16_t> indices_;
};

} // namespace rigel::mesh
