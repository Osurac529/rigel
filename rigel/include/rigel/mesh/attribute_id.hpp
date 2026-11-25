#pragma once

#include <cstdint>

namespace rigel::mesh {

using AttributeID = std::uint32_t;
constexpr inline std::uint32_t POSITION_ATTRIBUTE = 0;
constexpr inline std::uint32_t NORMAL_ATTRIBUTE = 1;
constexpr inline std::uint32_t TEXTURE_ATTRIBUTE_BEGIN = 2;
constexpr inline std::uint32_t TEXTURE_ATTRIBUTE = TEXTURE_ATTRIBUTE_BEGIN;
constexpr inline std::uint32_t TEXTURE_ATTRIBUTE_END = 5;
constexpr inline std::uint32_t TANGENT_ATTRIBUTE_BEGIN = 6;
constexpr inline std::uint32_t TANGENT_ATTRIBUTE = TANGENT_ATTRIBUTE_BEGIN;
constexpr inline std::uint32_t TANGENT_ATTRIBUTE_END = 9;
constexpr inline std::uint32_t COLOR_ATTRIBUTE_BEGIN = 10;
constexpr inline std::uint32_t COLOR_ATTRIBUTE = TEXTURE_ATTRIBUTE_BEGIN;
constexpr inline std::uint32_t COLOR_ATTRIBUTE_END = 11;

} // namespace rigel::mesh
