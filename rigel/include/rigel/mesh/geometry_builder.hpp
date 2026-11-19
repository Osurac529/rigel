#pragma once

#include <cstdint>

#include "rigel/math/math.hpp"

namespace rigel::mesh {

class Mesh;

struct GeometryBuilder {
  GeometryBuilder() = delete;

  // static Mesh BuildSphere(float radius, std::uint32_t subdivisions);

  static Mesh BuildCube(const math::vec3f &size = math::vec3f{1, 1, 1});
};

} // namespace rigel::mesh
