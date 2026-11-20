#pragma once

#include <variant>
#include <vector>

#include "rigel/math/math.hpp"

namespace rigel::mesh {

using Attribute = std::variant<math::vec2f, math::vec3f, math::vec4f>;

using AttributeVector =
    std::variant<std::vector<math::vec2f>, std::vector<math::vec3f>, std::vector<math::vec4f>>;

} // namespace rigel::mesh
