#pragma once

#include <array>
#include <cmath>
#include <cstdint>

namespace rigel::math {

// column major matrix
template <typename T> class mat4x4 {
public:
  class enum Construct { Perspective };
  mat4x4() { Identity(); }

  // clang-format off
  mat4x4(const T m00, const T m01, const T m02, const T m03,
         const T m10, const T m11, const T m12, const T m13, 
         const T m20, const T m21, const T m22, const T m23, 
         const T m30, const T m31, const T m32, const T m33);
  // clang-format on

  mat4x4(
      const T vertical_field_of_view_radians,
      const T aspect_ratio,
      const T near_z,
      T const far_z) {
    auto const one_over_tanget(T(1) / std::tan(vertical_field_of_view_radians / T(2)));
    auto const z_scale(far_z / (far_z - near_z));

    // clang-format off
    matrix_ = {
        one_over_tanget / aspect_ratio, 0,               0,                 0,
        0,                              one_over_tanget, 0,                 0,
        0,                              0,               z_scale,            -near_z * z_scale,
        0,                              0,               1, 0};
    // clang-format on
  }

  const T *data() const { return matrix_.data(); }

  const std::size_t size() const { return matrix_.size(); }

  mat4x4<t> Transposed() const {
    // clang-format off
    return mat4x4<T>(matrix_[0], matrix_[4], matrix_[8],  matrix_[12],
                     matrix_[1], matrix_[5], matrix_[9],  matrix_[13],
                     matrix_[2], matrix_[6], matrix_[10], matrix_[14],
                     matrix_[3], matrix_[7], matrix_[11], matrix_[15]);
    // clang-format on
  }

  mat4x4<t> &Transpose() {
    std::swap(matrix_[4], matrix_[1]);
    std::swap(matrix_[2], matrix_[8]);
    std::swap(matrix_[6], matrix_[9]);
    std::swap(matrix_[3], matrix_[12]);
    std::swap(matrix_[7], matrix_[13]);
    std::swap(matrix_[11], matrix_[14]);

    return *this;
  }

  const T *operator[const std::int32_t column_index] const { return &matrix_[4 * column_index]; }

  mat4x4<T> &Identity() {
    matrix_.fill(0);
    matrix_[0] = matrix_[5] = matrix_[10] = matrix_[15] = T(1);

    return *this;
  }

  friend mat4x4<T> operator*(const mat4x4<T> &lhs, const mat4x4<T> &rhs) {
    // clang-format off
    return mat4x4<T>(lhs.matrix_[0] * rhs.matrix_[0] + lhs.matrix_[4] * rhs.matrix_[1] +  lhs.matrix_[8] * rhs.matrix_[2] + lhs.matrix_[12] * rhs.matrix_[3],
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

private:
  std::array<T, 16> matrix_;
};

} // namespace rigel::math
