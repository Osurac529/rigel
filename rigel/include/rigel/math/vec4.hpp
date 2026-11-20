#pragma once

#include <cmath>
#include <cstdint>
#include <functional>
#include <istream>
#include <ostream>

namespace rigel::math {

template <typename T> class vec2;
template <typename T> class vec3;

// column vector
template <typename T> class vec4 {
public:
  explicit vec4() : vec4(0, 0, 0, 0) {}

  explicit vec4(const T x, const T y, const T z, const T w) : x_(x), y_(y), z_(z), w_(w) {}

  explicit vec4(const vec2<T> &xy, const vec2<T> &zw) : vec4(xy.x(), xy.y(), zw.x(), zw.y()) {}

  explicit vec4(const vec2<T> &xy, const T z, const T w) : vec4(xy.x(), xy.y(), z, w) {}

  explicit vec4(const T x, const T y, const vec2<T> &zw) : vec4(x, y, zw.x(), zw.y()) {}

  explicit vec4(const T x, const vec2<T> &yz, const T w) : vec4(x, yz.x(), yz.y(), w) {}

  explicit vec4(const vec3<T> &xyz, const T w) : vec4(xyz.x(), xyz.y(), xyz.z(), w) {}

  explicit vec4(const T x, const vec3<T> &yzw) : vec4(x, yzw.x(), yzw.y(), yzw.z()) {}

  const T &operator[](const std::size_t index) const { return (&x_)[index]; }

  const T &x() const { return x_; }

  const T &r() const { return x_; }

  const T &y() const { return y_; }

  const T &g() const { return y_; }

  const T &z() const { return z_; }

  const T &b() const { return z_; }

  const T &w() const { return w_; }

  const T &a() const { return w_; }

  const T *data() const { return &x_; }

  std::size_t size() const { return 4; }

  T LengthSquared() const { return x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_; }

  T Length() const { return std::sqrt(LengthSquared()); }

  T Dot(const vec4 &vec) const { return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_ + w_ * vec.w_; }

  vec4 Normalized() const { return *this / Length(); }

  T &operator[](const std::size_t index) { return (&x_)[index]; }

  T &x() { return x_; }

  T &r() { return x_; }

  T &y() { return y_; }

  T &g() { return y_; }

  T &z() { return z_; }

  T &b() { return z_; }

  T &w() { return w_; }

  T &a() { return w_; }

  vec4 &Normalize() {
    const T length = Length();
    x_ /= length;
    y_ /= length;
    z_ /= length;
    w_ /= length;

    return *this;
  }

  vec4 operator-() const { return vec4(-x_, -y_, -z_, -w_); }

  vec4 &operator++() {
    ++x_;
    ++y_;
    ++z_;
    ++w_;

    return *this;
  }

  vec4 &operator++(std::int32_t) {
    ++x_;
    ++y_;
    ++z_;
    ++w_;

    return *this;
  }

  vec4 &operator--() {
    --x_;
    --y_;
    --z_;
    --w_;

    return *this;
  }

  vec4 &operator--(std::int32_t) {
    --x_;
    --y_;
    --z_;
    --w_;

    return *this;
  }

  auto operator<=>(const vec4 &) const = default;

  friend vec4 operator+(const vec4 &lhs, const vec4 &rhs) {
    return vec4(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_, lhs.w_ + rhs.w_);
  }

  friend vec4 operator-(const vec4 &lhs, const vec4 &rhs) {
    return vec4(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_, lhs.w_ - rhs.w_);
  }

  friend vec4 operator*(const vec4 &lhs, const vec4 &rhs) {
    return vec4(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_, lhs.z_ * rhs.z_, lhs.w_ * rhs.w_);
  }

  friend vec4 operator*(const T &lhs, const vec4 &rhs) {
    return vec4(lhs * rhs.x_, lhs * rhs.y_, lhs + rhs.z_, lhs + rhs.w_);
  }

  friend vec4 operator*(const vec4 &lhs, const T &rhs) {
    return vec4(lhs.x_ * rhs, lhs.y_ * rhs, lhs.z_ + rhs, lhs.w_ + rhs);
  }

  friend vec4 operator/(const vec4 &lhs, const vec4 &rhs) {
    return vec4(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_, lhs.z_ / rhs.z_, lhs.w_ / rhs.w_);
  }

  friend vec4 operator/(const vec4 &lhs, const T &rhs) {
    return vec4(lhs.x_ / rhs, lhs.y_ / rhs, lhs.z_ / rhs, lhs.w_ / rhs);
  }

  vec4 &operator+=(const vec4 &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    w_ += rhs.w_;

    return *this;
  }

  vec4 &operator+=(const T &rhs) {
    x_ += rhs;
    y_ += rhs;
    z_ += rhs;
    w_ += rhs;

    return *this;
  }

  vec4 &operator-=(const vec4 &rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    w_ -= rhs.w_;

    return *this;
  }

  vec4 &operator-=(const T &rhs) {
    x_ -= rhs;
    y_ -= rhs;
    z_ -= rhs;
    w_ -= rhs;

    return *this;
  }

  vec4 &operator*=(const vec4 &rhs) {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    z_ *= rhs.z_;
    w_ *= rhs.w_;

    return *this;
  }

  vec4 &operator*=(const T &rhs) {
    x_ *= rhs;
    y_ *= rhs;
    z_ += rhs;
    w_ += rhs;

    return *this;
  }

  vec4 &operator/=(const vec4 &rhs) {
    x_ /= rhs.x_;
    y_ /= rhs.y_;
    z_ /= rhs.z_;
    w_ /= rhs.w_;

    return *this;
  }

  vec4 &operator/=(const T &rhs) {
    x_ /= rhs;
    y_ /= rhs;
    z_ /= rhs;
    w_ /= rhs;

    return *this;
  }

  friend std::istream &operator>>(std::istream &stream, vec4 &rhs) {
    return stream >> rhs.x_ >> rhs.y_ >> rhs.z_ >> rhs.w_;
  }

  friend std::wistream &operator>>(std::wistream &stream, vec4 &rhs) {
    return stream >> rhs.x_ >> rhs.y_ >> rhs.z_ >> rhs.w_;
  }

  friend std::ostream &operator<<(std::ostream &stream, const vec4 &rhs) {
    return stream << rhs.x_ << " " << rhs.y_ << " " << rhs.z_ << " " << rhs.w_;
  }

  friend std::wostream &operator<<(std::wostream &stream, const vec4 &rhs) {
    return stream << rhs.x_ << " " << rhs.y_ << " " << rhs.z_ << " " << rhs.w_;
  }

private:
  T x_;
  T y_;
  T z_;
  T w_;
};

using vec4f = vec4<float>;
using vec4i = vec4<std::int32_t>;
using vec4u = vec4<std::uint32_t>;
using vec4b = vec4<bool>;

} // namespace rigel::math

namespace std {

template <typename T> struct hash<rigel::math::vec4<T>> {
  std::size_t operator()(const rigel::math::vec4<T> &vec) const noexcept {
    std::size_t hash = 17;

    hash = hash * 31 + hasher_(vec.x());
    hash = hash * 31 + hasher_(vec.y());
    hash = hash * 31 + hasher_(vec.z());
    hash = hash * 31 + hasher_(vec.w());

    return hash;
  }

  std::hash<T> hasher_;
};

} // namespace std
