#include "rigel/mesh/geometry_builder.hpp"

#include "rigel/math/math.hpp"
#include "rigel/mesh/mesh.hpp"
#include "rigel/mesh/mesh_builder.hpp"

namespace rigel::mesh {

// Mesh BuildSphere(float radius, std::uint32_t subdivisions);

Mesh GeometryBuilder::BuildCube(const math::vec3f &size, const Options &options) {
  const std::vector<math::vec3f> positions = {
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

  std::vector<std::uint16_t> indices = {
      // clang-format off
      // front
      0, 3, 1,
      1, 3, 2,

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

  const std::vector<math::vec2f> texture_coordinates = {
      math::vec2f{0, 0}, math::vec2f{1, 0}, math::vec2f{1, 1}, math::vec2f{0, 1}};

  const std::vector<std::uint16_t> texture_coordinate_indices = {
      // clang-format off
      3, 0, 2,
      2, 0, 1,

      0, 2, 3,
      1, 2, 0,

      0, 2, 3,
      1, 2, 0,

      1, 2, 0,
      0, 2, 3,

      1, 2, 0,
      0, 2, 3,

      3, 0, 2,
      2, 0, 1
      // clang-format on
  };

  MeshBuilder builder;
  Vertex vertex;

  for (std::size_t i = 0; i < indices.size(); ++i) {
    vertex.Set(POSITION_ATTRIBUTE, positions[indices[i]] * size);

    if (options.texture_coordinates) {
      vertex.Set(TEXTURE_ATTRIBUTE, texture_coordinates[texture_coordinate_indices[i]]);
    }

    builder.Add(vertex);
  }

  return builder.Build();
}

Mesh GeometryBuilder::BuildCube(const Options &options) {
  return BuildCube(math::vec3f{1, 1, 1}, options);
}

} // namespace rigel::mesh