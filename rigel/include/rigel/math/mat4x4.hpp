#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <ostream>
#include <sstream>

#include "rigel/math/tags.hpp"

namespace rigel::math {

template <typename T> class vec2;
template <typename T> class vec3;
template <typename T> class vec4;
template <typename T> class mat3x3;

// column major matrix
template <typename T> class mat4x4 {
public:
  mat4x4() { Identity(); }

  mat4x4(
      const vec4<T> &column0,
      const vec4<T> &column1,
      const vec4<T> &column2,
      const vec4<T> &column3) {
    std::memcpy(&matrix_[0], column0.data(), column0.size() * sizeof(T));
    std::memcpy(&matrix_[4], column1.data(), column1.size() * sizeof(T));
    std::memcpy(&matrix_[8], column2.data(), column2.size() * sizeof(T));
    std::memcpy(&matrix_[12], column3.data(), column3.size() * sizeof(T));
  }

  // clang-format off
  mat4x4(const T m00, const T m01, const T m02, const T m03,   // column 0
         const T m10, const T m11, const T m12, const T m13,   // column 1
         const T m20, const T m21, const T m22, const T m23,   // column 2
         const T m30, const T m31, const T m32, const T m33) { // column 3
      matrix_[0] = m00;
      matrix_[1] = m01;
      matrix_[2] = m02;
      matrix_[3] = m03;
      matrix_[4] = m10;
      matrix_[5] = m11;
      matrix_[6] = m12;
      matrix_[7] = m13;
      matrix_[8] = m20;
      matrix_[9] = m21;
      matrix_[10] = m22;
      matrix_[11] = m23;
      matrix_[12] = m30;
      matrix_[13] = m31;
      matrix_[14] = m32;
      matrix_[15] = m33;
  }
  // clang-format on

  mat4x4(const mat3x3<T> &matrix) : mat4x4(matrix.column(0), matrix.column(1), matrix.column(2)) {}

  mat4x4(
      const T vertical_field_of_view_radians,
      const T aspect_ratio,
      const T near_z,
      const T far_z) {
    const auto one_over_tanget = T(1) / std::tan(vertical_field_of_view_radians / T(2));
    const auto z_scale = far_z / (far_z - near_z);

    // clang-format off
    matrix_ = {
        one_over_tanget / aspect_ratio, 0,               0,                 0,
        0,                              one_over_tanget, 0,                 0,
        0,                              0,               z_scale,           1,
        0,                              0,               -near_z * z_scale, 0
    };
    // clang-format on
  }

  //
  // @param eye Position of the camera in world space.
  // @param target Position of the target, what the eye is looking at.
  // @param up Up direction normalized.
  //
  mat4x4(const vec3<T> &eye, const vec3<T> &target, const vec3<T> &up = {0, 1, 0}) {
    const auto zaxis = (target - eye).Normalized();
    const auto xaxis = up.Cross(zaxis).Normalized();
    const auto yaxis = zaxis.Cross(xaxis);

    matrix_ = {
        xaxis.x(), yaxis.x(), zaxis.x(), 0, xaxis.y(),       yaxis.y(),       zaxis.y(),       0,
        xaxis.z(), yaxis.z(), zaxis.z(), 0, -xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye), 1};
  }

  mat4x4(const MakeXRotationT, const T angle) {
    // clang-format off
    matrix_ = {1, 0,                0,               0,  // column 0
               0, std::cos(angle),  std::sin(angle), 0,  // column 1
               0, -std::sin(angle), std::cos(angle), 0,  // column 2
               0, 0,                0,               1}; // column 3
    // clang-format on
  }

  mat4x4(const MakeYRotationT, const T angle) {
    // clang-format off
    matrix_ = {std::cos(angle), 0, -std::sin(angle), 0,  // column 0
               0,               1, 0,                0,  // column 1
               std::sin(angle), 0, std::cos(angle),  0,  // column 2
               0,               0, 0,                1}; // column 3
    // clang-format on
  }

  mat4x4(const MakeZRotationT, const T angle) {
    // clang-format off
    matrix_ = {std::cos(angle),  std::sin(angle), 0, 0,  // column 0
               -std::sin(angle), std::cos(angle), 0, 0,  // column 1
               0,                0,               1, 0,  // column 2
               0,                0,               0, 1}; // column 3
    // clang-format on
  }

  mat4x4(const vec4<T> &translation)
      : mat4x4(vec4<T>(1, 0, 0, 0), vec4<T>(0, 1, 0, 0), vec4<T>(0, 0, 1, 0), translation) {}

  mat4x4(const vec3<T> &scale) {
    matrix_.fill(0);
    matrix_[0] = scale.x();
    matrix_[5] = scale.y();
    matrix_[10] = scale.z();
    matrix_[15] = T(1);
  }

  const T *data() const { return matrix_.data(); }

  const std::size_t size() const { return matrix_.size(); }

  mat4x4 Transposed() const {
    // clang-format off
    return mat4x4(matrix_[0], matrix_[4], matrix_[8],  matrix_[12],
                  matrix_[1], matrix_[5], matrix_[9],  matrix_[13],
                  matrix_[2], matrix_[6], matrix_[10], matrix_[14],
                  matrix_[3], matrix_[7], matrix_[11], matrix_[15]);
    // clang-format on
  }

  mat4x4 &Transpose() {
    std::swap(matrix_[4], matrix_[1]);
    std::swap(matrix_[2], matrix_[8]);
    std::swap(matrix_[6], matrix_[9]);
    std::swap(matrix_[3], matrix_[12]);
    std::swap(matrix_[7], matrix_[13]);
    std::swap(matrix_[11], matrix_[14]);

    return *this;
  }

  const T *operator[](const std::size_t column_index) const {
    return &matrix_[4ULL * column_index];
  }

  vec4<T> row(const std::size_t row_index) const {
    return vec3<T>(
        matrix_[row_index], matrix_[row_index + 4], matrix_[row_index + 8],
        matrix_[row_index + 12]);
  }

  vec4<T> column(const std::size_t column_index) const {
    return vec4<T>(
        matrix_[4ULL * column_index], matrix_[4ULL * column_index + 1],
        matrix_[4ULL * column_index + 2], matrix_[4ULL * column_index + 3]);
  }

  mat4x4 &Identity() {
    matrix_.fill(0);
    matrix_[0] = matrix_[5] = matrix_[10] = matrix_[15] = T(1);

    return *this;
  }

  friend mat4x4 operator*(const mat4x4 &lhs, const mat4x4 &rhs) {
    // clang-format off
    return mat4x4(lhs.matrix_[0] * rhs.matrix_[0] + lhs.matrix_[4] * rhs.matrix_[1] +  lhs.matrix_[8] * rhs.matrix_[2] + lhs.matrix_[12] * rhs.matrix_[3],
                  lhs.matrix_[1] * rhs.matrix_[0] + lhs.matrix_[5] * rhs.matrix_[1] +  lhs.matrix_[9] * rhs.matrix_[2] + lhs.matrix_[13] * rhs.matrix_[3],
                  lhs.matrix_[2] * rhs.matrix_[0] + lhs.matrix_[6] * rhs.matrix_[1] + lhs.matrix_[10] * rhs.matrix_[2] + lhs.matrix_[14] * rhs.matrix_[3],
                  lhs.matrix_[3] * rhs.matrix_[0] + lhs.matrix_[7] * rhs.matrix_[1] + lhs.matrix_[11] * rhs.matrix_[2] + lhs.matrix_[15] * rhs.matrix_[3],
     
                  lhs.matrix_[0] * rhs.matrix_[4] + lhs.matrix_[4] * rhs.matrix_[5] +  lhs.matrix_[8] * rhs.matrix_[6] + lhs.matrix_[12] * rhs.matrix_[7],
                  lhs.matrix_[1] * rhs.matrix_[4] + lhs.matrix_[5] * rhs.matrix_[5] +  lhs.matrix_[9] * rhs.matrix_[6] + lhs.matrix_[13] * rhs.matrix_[7],
                  lhs.matrix_[2] * rhs.matrix_[4] + lhs.matrix_[6] * rhs.matrix_[5] + lhs.matrix_[10] * rhs.matrix_[6] + lhs.matrix_[14] * rhs.matrix_[7],
                  lhs.matrix_[3] * rhs.matrix_[4] + lhs.matrix_[7] * rhs.matrix_[5] + lhs.matrix_[11] * rhs.matrix_[6] + lhs.matrix_[15] * rhs.matrix_[7],

                  lhs.matrix_[0] * rhs.matrix_[8] + lhs.matrix_[4] * rhs.matrix_[9] +  lhs.matrix_[8] * rhs.matrix_[10] + lhs.matrix_[12] * rhs.matrix_[11],
                  lhs.matrix_[1] * rhs.matrix_[8] + lhs.matrix_[5] * rhs.matrix_[9] +  lhs.matrix_[9] * rhs.matrix_[10] + lhs.matrix_[13] * rhs.matrix_[11],
                  lhs.matrix_[2] * rhs.matrix_[8] + lhs.matrix_[6] * rhs.matrix_[9] + lhs.matrix_[10] * rhs.matrix_[10] + lhs.matrix_[14] * rhs.matrix_[11],
                  lhs.matrix_[3] * rhs.matrix_[8] + lhs.matrix_[7] * rhs.matrix_[9] + lhs.matrix_[11] * rhs.matrix_[10] + lhs.matrix_[15] * rhs.matrix_[11],

                  lhs.matrix_[0] * rhs.matrix_[12] + lhs.matrix_[4] * rhs.matrix_[13] +  lhs.matrix_[8] * rhs.matrix_[14] + lhs.matrix_[12] * rhs.matrix_[15],
                  lhs.matrix_[1] * rhs.matrix_[12] + lhs.matrix_[5] * rhs.matrix_[13] +  lhs.matrix_[9] * rhs.matrix_[14] + lhs.matrix_[13] * rhs.matrix_[15],
                  lhs.matrix_[2] * rhs.matrix_[12] + lhs.matrix_[6] * rhs.matrix_[13] + lhs.matrix_[10] * rhs.matrix_[14] + lhs.matrix_[14] * rhs.matrix_[15],
                  lhs.matrix_[3] * rhs.matrix_[12] + lhs.matrix_[7] * rhs.matrix_[13] + lhs.matrix_[11] * rhs.matrix_[14] + lhs.matrix_[15] * rhs.matrix_[15]);
    // clang-format on
  }

  friend std::ostream &operator<<(std::ostream &stream, const mat4x4 &rhs) {
    std::size_t width = 0;
    constexpr std::streamsize precision = 4;

    for (const auto value : rhs.matrix_) {
      std::ostringstream os;
      os << std::setprecision(precision) << std::fixed << value;
      width = std::max(width, os.str().length());
    }

    // clang-format off
    return stream << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[0] << ' ' 
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[4] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[8] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[12] << '\n'
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[1] << ' ' 
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[5] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[9] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[13] << '\n'
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[2] << ' ' 
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[6] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[10] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[14] << '\n'
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[3] << ' ' 
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[7] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[11] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[15];
    // clang-format on
  }

private:
  std::array<T, 16> matrix_;
};

using mat4x4f = mat4x4<float>;

} // namespace rigel::math
