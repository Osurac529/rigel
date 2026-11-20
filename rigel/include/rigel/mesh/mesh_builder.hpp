#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "rigel/mesh/vertex.hpp"

namespace rigel::mesh {

class Mesh;

class MeshBuilder {
public:
  enum class IndexMode {
    AUTO, // use 16-bit indices if they fit
    FULL  // always use 32-bit even if they can fit into 16-bit
  };

  struct Options {
    IndexMode index_mode = IndexMode::AUTO;
  };

  MeshBuilder &Add(const Vertex &vertex);

  Mesh Build(const Options &options = {});

private:
  std::uint32_t next_index_ = 0;
  std::unordered_map<Vertex, std::uint32_t> vertex_to_index_;
  std::vector<std::uint32_t> indices_;
};

} // namespace rigel::mesh
