#pragma once

#include <cstdint>

namespace rigel::mesh {

class Mesh;

class GeometryBuilder {
public:
  GeometryBuilder() = delete;

  // static Mesh BuildSphere(float radius, std::uint32_t subdivisions);

  static Mesh BuildCube(float size);
};

} // namespace rigel::mesh
