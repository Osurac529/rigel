#pragma once

#include <cstdint>

#include "rigel/math/math.hpp"

namespace rigel::mesh {

class Mesh;

struct GeometryBuilder {
  struct Options {
    bool texture_coordinates = false;
    bool normals = false;
    bool tangents = false; // requires texture_coordinates and normals
  };

  GeometryBuilder() = delete;

  // static Mesh BuildSphere(float radius, std::uint32_t subdivisions);

  static Mesh
  BuildCube(const math::vec3f &size = math::vec3f{1, 1, 1}, const Options &options = {});

  static Mesh BuildCube(const Options &options);
};

} // namespace rigel::mesh
