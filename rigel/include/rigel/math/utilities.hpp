#pragma once

#include <cmath>

namespace rigel::math {

constexpr double PI = 3.14159265358979323846;

inline float ToDegrees(const float radians) {
  return static_cast<float>(radians / PI * 180.0);
}

inline float ToRadians(const float degrees) {
  return static_cast<float>(degrees / 180.0 * PI);
}

} // namespace rigel::math
