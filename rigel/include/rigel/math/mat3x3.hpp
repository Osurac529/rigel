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
template <typename T> class mat4x4;

// column major matrix
template <typename T> class mat3x3 {
public:
  mat3x3() { Identity(); }

  mat3x3(const vec3<T> &column0, const vec3<T> &column1, const vec3<T> &column2) {
    std::memcpy(&matrix_[0], column0.data(), column0.size() * sizeof(T));
    std::memcpy(&matrix_[3], column1.data(), column1.size() * sizeof(T));
    std::memcpy(&matrix_[6], column2.data(), column2.size() * sizeof(T));
  }

  // clang-format off
  mat3x3(const T m00, const T m01, const T m02,   // column 0
         const T m10, const T m11, const T m12,   // column 1
         const T m20, const T m21, const T m22) { // column 2
      matrix_[0] = m00;
      matrix_[1] = m01;
      matrix_[2] = m02;
      matrix_[3] = m10;
      matrix_[4] = m11;
      matrix_[5] = m12;
      matrix_[6] = m20;
      matrix_[7] = m21;
      matrix_[8] = m22;
  }
  // clang-format on

  mat3x3(const mat4x4<T> &matrix)
      : mat3x3(vec3(matrix.column(0)), vec3(matrix.column(1)), vec3(matrix.column(2))) {}

  mat3x3(const MakeXRotationT, const T angle) {
    // clang-format off
    matrix_ = {1, 0,                0,                // column 0
               0, std::cos(angle),  std::sin(angle),  // column 1
               0, -std::sin(angle), std::cos(angle)}; // column 2
    // clang-format on
  }

  mat3x3(const MakeYRotationT, const T angle) {
    // clang-format off
    matrix_ = {std::cos(angle), 0, -std::sin(angle), // column 0
               0,               1, 0,                // column 1
               std::sin(angle), 0, std::cos(angle)}; // column 2
    // clang-format on
  }

  mat3x3(const MakeZRotationT, const T angle) {
    // clang-format off
    matrix_ = {std::cos(angle),  std::sin(angle), 0,  // column 0
               -std::sin(angle), std::cos(angle), 0,  // column 1
               0,                0,               1}; // column 2
    // clang-format on
  }

  mat3x3(const vec3<T> &scale) {
    matrix_.fill(0);
    matrix_[0] = scale.x();
    matrix_[4] = scale.y();
    matrix_[8] = scale.z();
  }

  const T *data() const { return matrix_.data(); }

  const std::size_t size() const { return matrix_.size(); }

  mat3x3 Transposed() const {
    // clang-format off
    return mat3x3(matrix_[0], matrix_[1], matrix_[2], 
                  matrix_[3], matrix_[4], matrix_[5], 
                  matrix_[6], matrix_[7], matrix_[8]);
    // clang-format on
  }

  mat3x3 &Transpose() {
    std::swap(matrix_[3], matrix_[1]);
    std::swap(matrix_[2], matrix_[6]);
    std::swap(matrix_[5], matrix_[7]);

    return *this;
  }

  const T *operator[](const std::size_t column_index) const {
    return &matrix_[3ULL * column_index];
  }

  vec3<T> row(const std::size_t row_index) const {
    return vec3<T>(matrix_[row_index], matrix_[row_index + 3], matrix_[row_index + 6]);
  }

  vec3<T> column(const std::size_t column_index) const {
    return vec3<T>(
        matrix_[3ULL * column_index], matrix_[3ULL * column_index + 1],
        matrix_[3ULL * column_index + 2]);
  }

  mat3x3 &Identity() {
    matrix_.fill(0);
    matrix_[0] = matrix_[4] = matrix_[8] = T(1);

    return *this;
  }

  T Determinant() const {
    return (matrix_[0] * matrix_[4] * matrix_[8] + matrix_[3] * matrix_[7] * matrix_[2] +
            matrix_[6] * matrix_[1] * matrix_[5]) -
           (matrix_[6] * matrix_[4] * matrix_[2] + matrix_[3] * matrix_[1] * matrix_[8] +
            matrix_[0] * matrix_[7] * matrix_[5]);
  }

  mat3x3 &Minors() {
    std::array new_matrix = {
        matrix_[4] * matrix_[8] - matrix_[7] * matrix_[5],
        matrix_[3] * matrix_[8] - matrix_[6] * matrix_[5],
        matrix_[3] * matrix_[7] - matrix_[6] * matrix_[4],
        matrix_[1] * matrix_[8] - matrix_[7] * matrix_[2],
        matrix_[0] * matrix_[8] - matrix_[6] * matrix_[2],
        matrix_[0] * matrix_[7] - matrix_[6] * matrix_[1],
        matrix_[1] * matrix_[5] - matrix_[4] * matrix_[2],
        matrix_[0] * matrix_[5] - matrix_[3] * matrix_[2],
        matrix_[0] * matrix_[4] - matrix_[3] * matrix_[1]};

    matrix_.swap(new_matrix);

    return *this;
  }

  mat3x3 Minorsed() const {
    return mat3x3(
        matrix_[4] * matrix_[8] - matrix_[7] * matrix_[5],
        matrix_[3] * matrix_[8] - matrix_[6] * matrix_[5],
        matrix_[3] * matrix_[7] - matrix_[6] * matrix_[4],
        matrix_[1] * matrix_[8] - matrix_[7] * matrix_[2],
        matrix_[0] * matrix_[8] - matrix_[6] * matrix_[2],
        matrix_[0] * matrix_[7] - matrix_[6] * matrix_[1],
        matrix_[1] * matrix_[5] - matrix_[4] * matrix_[2],
        matrix_[0] * matrix_[5] - matrix_[3] * matrix_[2],
        matrix_[0] * matrix_[4] - matrix_[3] * matrix_[1]);
  }

  mat3x3 &Cofactor() {
    std::array new_matrix = {
        matrix_[4] * matrix_[8] - matrix_[7] * matrix_[5],
        matrix_[6] * matrix_[5] - matrix_[3] * matrix_[8],
        matrix_[3] * matrix_[7] - matrix_[6] * matrix_[4],
        matrix_[7] * matrix_[2] - matrix_[1] * matrix_[8],
        matrix_[0] * matrix_[8] - matrix_[6] * matrix_[2],
        matrix_[6] * matrix_[1] - matrix_[0] * matrix_[7],
        matrix_[1] * matrix_[5] - matrix_[4] * matrix_[2],
        matrix_[3] * matrix_[2] - matrix_[0] * matrix_[5],
        matrix_[0] * matrix_[4] - matrix_[3] * matrix_[1]};

    matrix_.swap(new_matrix);

    return *this;
  }

  mat3x3 Cofactored() const {
    return mat3x3(
        matrix_[4] * matrix_[8] - matrix_[7] * matrix_[5],
        matrix_[6] * matrix_[5] - matrix_[3] * matrix_[8],
        matrix_[3] * matrix_[7] - matrix_[6] * matrix_[4],
        matrix_[7] * matrix_[2] - matrix_[1] * matrix_[8],
        matrix_[0] * matrix_[8] - matrix_[6] * matrix_[2],
        matrix_[6] * matrix_[1] - matrix_[0] * matrix_[7],
        matrix_[1] * matrix_[5] - matrix_[4] * matrix_[2],
        matrix_[3] * matrix_[2] - matrix_[0] * matrix_[5],
        matrix_[0] * matrix_[4] - matrix_[3] * matrix_[1]);
  }

  mat3x3 &Adjugate() {
    // https://www.ck12.org/flexi/cbse-math/transpose-of-a-matrix-symmetric-and-skew-symmetric-matrix/how-do-you-find-the-adjoint-of-a-3x3-matrix/
    Cofactor();

    Transpose();

    return *this;
  }

  mat3x3 Adjugated() const { return Cofactored().Transposed(); }

  mat3x3 &Inverse() {
    const auto inverse_determinant = T(1) / Determinant();

    Adjugate();

    for (auto &element : matrix_) {
      element *= inverse_determinant;
    }

    return *this;
  }

  mat3x3 Inversed() const { return (T(1) / Determinant()) * Adjugated(); }

  friend mat3x3 operator*(const T scale, const mat3x3 &rhs) {
    return mat3x3(
        matrix_[0] * scale, matrix_[1] * scale, matrix_[2] * scale, matrix_[3] * scale,
        matrix_[4] * scale, matrix_[5] * scale, matrix_[6] * scale, matrix_[7] * scale,
        matrix_[8] * scale);
  }

  friend mat3x3 operator*(const mat3x3 &rhs, const T scale) {
    return mat3x3(
        matrix_[0] * scale, matrix_[1] * scale, matrix_[2] * scale, matrix_[3] * scale,
        matrix_[4] * scale, matrix_[5] * scale, matrix_[6] * scale, matrix_[7] * scale,
        matrix_[8] * scale);
  }

  friend mat3x3 operator*(const mat3x3 &lhs, const mat3x3 &rhs) {
    // clang-format off
    return mat3x3(lhs.matrix_[0] * rhs.matrix_[0] + lhs.matrix_[3] * rhs.matrix_[1] + lhs.matrix_[6] * rhs.matrix_[2],
                  lhs.matrix_[1] * rhs.matrix_[0] + lhs.matrix_[4] * rhs.matrix_[1] + lhs.matrix_[7] * rhs.matrix_[2],
                  lhs.matrix_[2] * rhs.matrix_[0] + lhs.matrix_[5] * rhs.matrix_[1] + lhs.matrix_[8] * rhs.matrix_[2],
     
                  lhs.matrix_[0] * rhs.matrix_[3] + lhs.matrix_[3] * rhs.matrix_[4] + lhs.matrix_[6] * rhs.matrix_[5],
                  lhs.matrix_[1] * rhs.matrix_[3] + lhs.matrix_[4] * rhs.matrix_[4] + lhs.matrix_[7] * rhs.matrix_[5],
                  lhs.matrix_[2] * rhs.matrix_[3] + lhs.matrix_[5] * rhs.matrix_[4] + lhs.matrix_[8] * rhs.matrix_[5],

                  lhs.matrix_[0] * rhs.matrix_[6] + lhs.matrix_[3] * rhs.matrix_[7] + lhs.matrix_[6] * rhs.matrix_[8],
                  lhs.matrix_[1] * rhs.matrix_[6] + lhs.matrix_[4] * rhs.matrix_[7] + lhs.matrix_[7] * rhs.matrix_[8],
                  lhs.matrix_[2] * rhs.matrix_[6] + lhs.matrix_[5] * rhs.matrix_[7] + lhs.matrix_[8] * rhs.matrix_[8]);
    // clang-format on
  }

  friend std::ostream &operator<<(std::ostream &stream, const mat3x3 &rhs) {
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
                  << rhs.matrix_[3] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[6] << '\n'
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[1] << ' ' 
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[4] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[7] << '\n'
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[2] << ' ' 
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[5] << ' '
                  << std::setprecision(precision) << std::setw(width) << std::fixed << std::right
                  << rhs.matrix_[8];
    // clang-format on
  }

private:
  std::array<T, 9> matrix_;
};

using mat3x3f = mat3x3<float>;

} // namespace rigel::math
