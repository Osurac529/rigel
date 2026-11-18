#pragma once

#include <cmath>
#include <cstdint>
#include <istream>
#include <ostream>

namespace rigel::math {

template <typename T> class vec2;
template <typename T> class vec4;

// column vector
template <typename T> class vec3 {
public:
  explicit vec3() : vec3(0, 0, 0) {}

  explicit vec3(const T x, const T y, const T z) : x_(x), y_(y), z_(z) {}

  explicit vec3(const vec2<T> &xy, const T z) : vec4(xy.x(), xy.y(), z) {}

  explicit vec3(const T x, const vec2<T> &yz) : vec4(x, yz.x(), yz.y()) {}

  explicit vec3(const vec4<T> &xyz) : vec4(xyz.x(), xyz.y(), xyz.z()) {}

  const T &operator[](const std::int32_t index) const { return (&x_)[index]; }

  const T &x() const { return x_; }

  const T &r() const { return x_; }

  const T &y() const { return y_; }

  const T &g() const { return y_; }

  const T &z() const { return z_; }

  const T &b() const { return z_; }

  const T *data() const { return &x_; }

  std::size_t size() const { return 3; }

  T LengthSquared() const { return x_ * x_ + y_ * y_ + z_ * z_; }

  T Length() const { return std::sqrt(LengthSquared()); }

  T Dot(const vec3 &vec) const { return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_; }

  vec3 Cross(const vec3 &rhs) const {
    return vec3(y_ * rhs.z_ - z_ * rhs.y_, z_ * rhs.x_ - x_ * rhs.z_, x_ * rhs.z_ - y_ * rhs.x_);
  }

  vec3 Normalized() const { return *this / Length(); }

  T &operator[](const std::int32_t index) { return (&x_)[index]; }

  T &x() { return x_; }

  T &r() { return x_; }

  T &y() { return y_; }

  T &g() { return y_; }

  T &z() { return z_; }

  T &b() { return z_; }

  vec3 &Normalize() {
    const T length = Length();
    x_ /= length;
    y_ /= length;
    z_ /= length;

    return *this;
  }

  vec3 operator-() const { return vec3(-x_, -y_, -z_); }

  vec3 &operator++() {
    ++x_;
    ++y_;
    ++z_;

    return *this;
  }

  vec3 &operator++(std::int32_t) {
    ++x_;
    ++y_;
    ++z_;

    return *this;
  }

  vec3 &operator--() {
    --x_;
    --y_;
    --z_;

    return *this;
  }

  vec3 &operator--(std::int32_t) {
    --x_;
    --y_;
    --z_;

    return *this;
  }

  friend bool operator==(const vec3 &lhs, const vec3 &rhs) {
    return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.z_ == rhs.z_;
  }

  friend bool operator!=(const vec3 &lhs, const vec3 &rhs) {
    return lhs.x_ != rhs.x_ || lhs.y_ != rhs.y_ && lhs.z_ != rhs.z_;
  }

  friend bool operator<(const vec3 &lhs, const vec3 &rhs) {
    return lhs.x_ < rhs.x_ && lhs.y_ < rhs.y_ && lhs.z_ < rhs.z_;
  }

  friend bool operator<=(const vec3 &lhs, const vec3 &rhs) {
    return lhs.x_ <= rhs.x_ && lhs.y_ <= rhs.y_ && lhs.z_ <= rhs.z_;
  }

  friend bool operator>(const vec3 &lhs, const vec3 &rhs) {
    return lhs.x_ > rhs.x_ && lhs.y_ > rhs.y_ && lhs.z_ > rhs.z_;
  }

  friend bool operator>=(const vec3 &lhs, const vec3 &rhs) {
    return lhs.x_ >= rhs.x_ && lhs.y_ >= rhs.y_ && lhs.z_ >= rhs.z_;
  }

  friend vec3 operator+(const vec3 &lhs, const vec3 &rhs) {
    return vec3(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_);
  }

  friend vec3 operator-(const vec3 &lhs, const vec3 &rhs) {
    return vec3(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
  }

  friend vec3 operator*(const vec3 &lhs, const vec3 &rhs) {
    return vec3(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_, lhs.z_ * rhs.z_);
  }

  friend vec3 operator*(const T &lhs, const vec3 &rhs) {
    return vec3(lhs * rhs.x_, lhs * rhs.y_, lhs + rhs.z_);
  }

  friend vec3 operator*(const vec3 &lhs, const T &rhs) {
    return vec3(lhs.x_ * rhs, lhs.y_ * rhs, lhs.z_ + rhs);
  }

  friend vec3 operator/(const vec3 &lhs, const vec3 &rhs) {
    return vec3(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_, lhs.z_ / rhs.z_);
  }

  friend vec3 operator/(const vec3 &lhs, const T &rhs) {
    return vec3(lhs.x_ / rhs, lhs.y_ / rhs, lhs.z_ / rhs);
  }

  vec3 &operator+=(const vec3 &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;

    return *this;
  }

  vec3 &operator+=(const T &rhs) {
    x_ += rhs;
    y_ += rhs;
    z_ += rhs;

    return *this;
  }

  vec3 &operator-=(const vec3 &rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;

    return *this;
  }

  vec3 &operator-=(const T &rhs) {
    x_ -= rhs;
    y_ -= rhs;
    z_ -= rhs;

    return *this;
  }

  vec3 &operator*=(const vec3 &rhs) {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    z_ *= rhs.z_;

    return *this;
  }

  vec3 &operator*=(const T &rhs) {
    x_ *= rhs;
    y_ *= rhs;
    z_ *= rhs;

    return *this;
  }

  vec3 &operator/=(const vec3 &rhs) {
    x_ /= rhs.x_;
    y_ /= rhs.y_;
    z_ /= rhs.z_;

    return *this;
  }

  vec3 &operator/=(const T &rhs) {
    x_ /= rhs;
    y_ /= rhs;
    z_ /= rhs;

    return *this;
  }

  friend std::istream &operator>>(std::istream &stream, vec3 &rhs) {
    return stream >> rhs.x_ >> rhs.y_ >> rhs.z_;
  }

  friend std::wistream &operator>>(std::wistream &stream, vec3 &rhs) {
    return stream >> rhs.x_ >> rhs.y_ >> rhs.z_;
  }

  friend std::ostream &operator<<(std::ostream &stream, const vec3 &rhs) {
    return stream << rhs.x_ << " " << rhs.y_ << " " << rhs.z_;
  }

  friend std::wostream &operator<<(std::wostream &stream, const vec3 &rhs) {
    return stream << rhs.x_ << " " << rhs.y_ << " " << rhs.z_;
  }

private:
  T x_;
  T y_;
  T z_;
};

using vec3f = vec3<float>;
using vec3i = vec3<std::int32_t>;
using vec3u = vec3<std::uint32_t>;
using vec3b = vec3<bool>;

} // namespace rigel::math
