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
      0, 3, 1,
      3, 2, 1,

      // right
      2, 5, 1,
      6, 5, 2,

      // top
      7, 2, 3,
      6, 2, 7,

      // left
      3, 0, 7,
      7, 0, 4,

      // back
      7, 4, 6,
      6, 4, 5,

      // bottom
      1, 5, 0,
      0, 5, 4
      // clang-format on
  };

  return Mesh(std::move(positions), std::move(indices));
}

} // namespace rigel::mesh