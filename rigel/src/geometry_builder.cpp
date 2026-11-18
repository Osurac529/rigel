#include "rigel/mesh/geometry_builder.hpp"

#include "rigel/math/math.hpp"
#include "rigel/mesh/mesh.hpp"

namespace rigel::mesh {

// Mesh BuildSphere(float radius, std::uint32_t subdivisions);

Mesh GeometryBuilder::BuildCube(const math::vec3f &size) {
  std::vector<math::vec3f> positions = {
      // clang-format off
      math::vec3f{-0.5f, -0.5f, -0.5f},
      math::vec3f{0.5f, -0.5f, -0.5f},
      math::vec3f{0.5f, 0.5f, -0.5f},
      math::vec3f{-0.5f, 0.5f, -0.5f},

      math::vec3f{-0.5f, -0.5f, 0.5f},
      math::vec3f{0.5f, -0.5f, 0.5f},
      math::vec3f{0.5f, 0.5f, 0.5f},
      math::vec3f{-0.5f, 0.5f, 0.5f},
      // clang-format on
  };

  for (auto &position : positions) {
    position *= size;
  }

  std::vector<std::uint16_t> indices = {
      // clang-format off
      // front
      0, 1, 3,
      3, 1, 2,

      // right
      2, 1, 5,
      6, 2, 5,

      // top
      7, 3, 2,
      6, 7, 2,

      // left
      3, 7, 0,
      7, 4, 0,

      // back
      7, 6, 4,
      6, 5, 4,

      // bottom
      1, 0, 5,
      0, 4, 5
      // clang-format on
  };

  return Mesh(std::move(positions), std::move(indices));
}

} // namespace rigel::mesh