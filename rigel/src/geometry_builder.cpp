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
      0, 5, 4,
      // clang-format on
  };

  const std::vector<math::vec2f> texture_coordinates = {
      math::vec2f{0, 0},
      math::vec2f{1, 0},
      math::vec2f{1, 1},
      math::vec2f{0, 1},
  };

  const std::vector<std::uint16_t> texture_coordinate_indices = {
      // clang-format off
      // front
      3, 0, 2,
      2, 0, 1,

      // right
      0, 2, 3,
      1, 2, 0,

      // top
      0, 2, 3,
      1, 2, 0,

      // left
      1, 2, 0,
      0, 2, 3,

      // back
      1, 2, 0,
      0, 2, 3,

      // bottom
      3, 0, 2,
      2, 0, 1,
      // clang-format on
  };

  const std::vector<math::vec3f> normals = {
      math::vec3f{1, 0, 0},  math::vec3f{-1, 0, 0}, math::vec3f{0, 1, 0},
      math::vec3f{0, -1, 0}, math::vec3f{0, 0, 1},  math::vec3f{0, 0, -1},
  };

  const std::vector<std::uint16_t> normal_indices = {
      // clang-format off
      // front
      5, 5, 5,
      5, 5, 5,

      // right
      0, 0, 0,
      0, 0, 0,

      // top
      2, 2, 2,
      2, 2, 2,

      // left
      1, 1, 1,
      1, 1, 1,

      // back
      4, 4, 4,
      4, 4, 4,

      // bottom
      3, 3, 3,
      3, 3, 3,
      // clang-format on
  };

  MeshBuilder builder;
  Vertex vertex;

  for (std::size_t i = 0; i < indices.size(); ++i) {
    vertex.Set(POSITION_ATTRIBUTE, positions[indices[i]] * size);

    if (options.texture_coordinates) {
      vertex.Set(TEXTURE_ATTRIBUTE, texture_coordinates[texture_coordinate_indices[i]]);
    }

    if (options.normals) {
      vertex.Set(NORMAL_ATTRIBUTE, normals[normal_indices[i]]);
    }

    builder.Add(vertex);
  }

  auto mesh = builder.Build();

  if (!options.tangents || (options.tangents && (!mesh.HasAttribute(TEXTURE_ATTRIBUTE) ||
                                                 !mesh.HasAttribute(NORMAL_ATTRIBUTE)))) {
    return mesh;
  }

  const auto vertex_count = mesh.GetVertexCount();
  std::vector<math::vec3f> accumulated_tangets(vertex_count);
  std::vector<math::vec3f> accumulated_bi_tangets(vertex_count);

  // https://marti.works/posts/post-calculating-tangents-for-your-mesh/post/
  mesh.VisitTriangleIndices(
      [&mesh, &accumulated_tangets, &accumulated_bi_tangets](
          const std::uint32_t index_a, const std::uint32_t index_b, std::uint32_t index_c) {
        const auto position_a = mesh.Get<math::vec3f>(POSITION_ATTRIBUTE, index_a);
        const auto edge_ba = mesh.Get<math::vec3f>(POSITION_ATTRIBUTE, index_b) - position_a;
        const auto edge_ca = mesh.Get<math::vec3f>(POSITION_ATTRIBUTE, index_c) - position_a;

        const auto texture_coordinate_a = mesh.Get<math::vec2f>(TEXTURE_ATTRIBUTE, index_a);
        const auto texture_ba =
            mesh.Get<math::vec2f>(TEXTURE_ATTRIBUTE, index_b) - texture_coordinate_a;
        const auto texture_ca =
            mesh.Get<math::vec2f>(TEXTURE_ATTRIBUTE, index_c) - texture_coordinate_a;

        auto determinant_factor = texture_ba.Cross(texture_ca);

        if (std::abs(determinant_factor) == 0) {
          return;
        }

        determinant_factor = 1.0f / determinant_factor;

        const math::vec3f tangent(
            determinant_factor * (texture_ca.y() * edge_ba.x() - texture_ba.y() * edge_ca.x()),
            determinant_factor * (texture_ca.y() * edge_ba.y() - texture_ba.y() * edge_ca.y()),
            determinant_factor * (texture_ca.y() * edge_ba.z() - texture_ba.y() * edge_ca.z()));

        accumulated_tangets[index_a] += tangent;
        accumulated_tangets[index_b] += tangent;
        accumulated_tangets[index_c] += tangent;

        const math::vec3f bi_tangent(
            determinant_factor * (texture_ba.x() * edge_ca.x() - texture_ca.x() * edge_ba.x()),
            determinant_factor * (texture_ba.x() * edge_ca.y() - texture_ca.x() * edge_ba.y()),
            determinant_factor * (texture_ba.x() * edge_ca.z() - texture_ca.x() * edge_ba.z()));

        accumulated_bi_tangets[index_a] += tangent;
        accumulated_bi_tangets[index_b] += tangent;
        accumulated_bi_tangets[index_c] += tangent;
      });

  for (std::uint32_t i = 0; i < vertex_count; ++i) {
    // Gram-Schmidt orthogonalize, todo: make this a function in vec3
    const auto normal = mesh.Get<math::vec3f>(NORMAL_ATTRIBUTE, i);
    auto tangent = accumulated_tangets[i] - normal * normal.Dot(accumulated_tangets[i]);

    // normalize the accumulated values
    tangent.Normalize();

    // handedness
    mesh.Set(
        TANGENT_ATTRIBUTE, i,
        math::vec4f(
            tangent, normal.Cross(accumulated_tangets[i]).Dot(accumulated_bi_tangets[i]) < 0
                         ? -1.0f
                         : 1.0f));
  }

  return mesh;
}

Mesh GeometryBuilder::BuildCube(const Options &options) {
  return BuildCube(math::vec3f{1, 1, 1}, options);
}

} // namespace rigel::mesh
