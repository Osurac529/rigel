#pragma once

#include <cmath>
#include <cstdint>
#include <istream>
#include <ostream>

namespace rigel::math {

template <typename T> class vec3;
template <typename T> class vec4;

// column vector
template <typename T> class vec2 {
public:
  explicit vec2() : vec2(0, 0) {}

  explicit vec2(const T x, const T y) : x_(x), y_(y) {}

  explicit vec2(const vec3<T> &xy) : vec2(xy.x(), xy.y()) {}

  explicit vec2(const vec4<T> &xy) : vec2(xy.x(), xy.y()) {}

  const T &operator[](const std::int32_t index) const { return (&x_)[index]; }

  const T &x() const { return x_; }

  const T &r() const { return x_; }

  const T &y() const { return y_; }

  const T &g() const { return y_; }

  const T *data() const { return &x_; }

  std::size_t size() const { return 2; }

  T LengthSquared() const { return x_ * x_ + y_ * y_; }

  T Length() const { return std::sqrt(LengthSquared()); }

  T Dot(const vec2 &vec) const { return x_ * vec.x_ + y_ * vec.y_; }

  T Cross(const vec2 &rhs) const { return x_ * rhs.y_ - y_ * rhs.x_; }

  vec2 Normalized() const { return *this / Length(); }

  T &operator[](const std::int32_t index) { return (&x_)[index]; }

  T &x() { return x_; }

  T &r() { return x_; }

  T &y() { return y_; }

  T &g() { return y_; }

  vec2 &Normalize() {
    const T length = Length();
    x_ /= length;
    y_ /= length;

    return *this;
  }

  vec2 operator-() const { return vec2(-x_, -y_); }

  vec2 &operator++() {
    ++x_;
    ++y_;

    return *this;
  }

  vec2 &operator++(std::int32_t) {
    ++x_;
    ++y_;

    return *this;
  }

  vec2 &operator--() {
    --x_;
    --y_;

    return *this;
  }

  vec2 &operator--(std::int32_t) {
    --x_;
    --y_;

    return *this;
  }

  friend bool operator==(const vec2 &lhs, const vec2 &rhs) {
    return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
  }

  friend bool operator!=(const vec2 &lhs, const vec2 &rhs) {
    return lhs.x_ != rhs.x_ || lhs.y_ != rhs.y_;
  }

  friend bool operator<(const vec2 &lhs, const vec2 &rhs) {
    return lhs.x_ < rhs.x_ && lhs.y_ < rhs.y_;
  }

  friend bool operator<=(const vec2 &lhs, const vec2 &rhs) {
    return lhs.x_ <= rhs.x_ && lhs.y_ <= rhs.y_;
  }

  friend bool operator>(const vec2 &lhs, const vec2 &rhs) {
    return lhs.x_ > rhs.x_ && lhs.y_ > rhs.y_;
  }

  friend bool operator>=(const vec2 &lhs, const vec2 &rhs) {
    return lhs.x_ >= rhs.x_ && lhs.y_ >= rhs.y_;
  }

  friend vec2 operator+(const vec2 &lhs, const vec2 &rhs) {
    return vec2(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
  }

  friend vec2 operator-(const vec2 &lhs, const vec2 &rhs) {
    return vec2(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
  }

  friend vec2 operator*(const vec2 &lhs, const vec2 &rhs) {
    return vec2(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_);
  }

  friend vec2 operator*(const T &lhs, const vec2 &rhs) { return vec2(lhs * rhs.x_, lhs * rhs.y_); }

  friend vec2 operator*(const vec2 &lhs, const T &rhs) { return vec2(lhs.x_ * rhs, lhs.y_ * rhs); }

  friend vec2 operator/(const vec2 &lhs, const vec2 &rhs) {
    return vec2(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_);
  }

  friend vec2 operator/(const vec2 &lhs, const T &rhs) { return vec2(lhs.x_ / rhs, lhs.y_ / rhs); }

  vec2 &operator+=(const vec2 &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;

    return *this;
  }

  vec2 &operator+=(const T &rhs) {
    x_ += rhs;
    y_ += rhs;

    return *this;
  }

  vec2 &operator-=(const vec2 &rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;

    return *this;
  }

  vec2 &operator-=(const T &rhs) {
    x_ -= rhs;
    y_ -= rhs;

    return *this;
  }

  vec2 &operator*=(const vec2 &rhs) {
    x_ *= rhs.x_;
    y_ *= rhs.y_;

    return *this;
  }

  vec2 &operator*=(const T &rhs) {
    x_ *= rhs;
    y_ *= rhs;

    return *this;
  }

  vec2 &operator/=(const vec2 &rhs) {
    x_ /= rhs.x_;
    y_ /= rhs.y_;

    return *this;
  }

  vec2 &operator/=(const T &rhs) {
    x_ /= rhs;
    y_ /= rhs;

    return *this;
  }

  friend std::istream &operator>>(std::istream &stream, vec2 &rhs) {
    return stream >> rhs.x_ >> rhs.y_;
  }

  friend std::wistream &operator>>(std::wistream &stream, vec2 &rhs) {
    return stream >> rhs.x_ >> rhs.y_;
  }

  friend std::ostream &operator<<(std::ostream &stream, const vec2 &rhs) {
    return stream << rhs.x_ << " " << rhs.y_;
  }

  friend std::wostream &operator<<(std::wostream &stream, const vec2 &rhs) {
    return stream << rhs.x_ << " " << rhs.y_;
  }

private:
  T x_;
  T y_;
};

using vec2f = vec2<float>;
using vec2i = vec2<std::int32_t>;
using vec2u = vec2<std::uint32_t>;
using vec2b = vec2<bool>;

} // namespace rigel::math
