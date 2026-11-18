#pragma once

#include <cmath>
#include <cstdint>
#include <istream>
#include <ostream>

namespace rigel::math {

// column vector
template <typename T> class vec3 {
public:
  explicit vec3() : x_(0), y_(0), z_(0) {}

  explicit vec3(const T x, const T y, const T z) : x_(x), y_(y), z_(z) {}

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

  T Dot(const vec3<T> &vec) const { return x_ * vec.x_ + y_ * vec.y_ + z_ * vec.z_; }

  vec3<T> Cross(const vec3<T> &rhs) const {
    return vec3<T>(y_ * rhs.z_ - z_ * rhs.y_, z_ * rhs.x_ - x_ * rhs.z_, x_ * rhs.z_ - y_ * rhs.x_);
  }

  vec3<T> Normalized() const { return *this / Length(); }

  T &operator[](const std::int32_t index) { return (&x_)[index]; }

  T &x() { return x_; }

  T &r() { return x_; }

  T &y() { return y_; }

  T &g() { return y_; }

  T &z() { return z_; }

  T &b() { return z_; }

  vec3<T> &Normalize() {
    const T length = Length();
    x_ /= length;
    y_ /= length;
    z_ /= length;

    return *this;
  }

  vec3<T> operator-() const { return vec3<T>(-x_, -y_, -z_); }

  vec3<T> &operator++() {
    ++x_;
    ++y_;
    ++z_;

    return *this;
  }

  vec3<T> &operator++(std::int32_t) {
    ++x_;
    ++y_;
    ++z_;

    return *this;
  }

  vec3<T> &operator--() {
    --x_;
    --y_;
    --z_;

    return *this;
  }

  vec3<T> &operator--(std::int32_t) {
    --x_;
    --y_;
    --z_;

    return *this;
  }

  friend bool operator==(const vec3<T> &lhs, const vec3<T> &rhs) {
    return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.z_ == rhs.z_;
  }

  friend bool operator!=(const vec3<T> &lhs, const vec3<T> &rhs) {
    return lhs.x_ != rhs.x_ || lhs.y_ != rhs.y_ && lhs.z_ != rhs.z_;
  }

  friend bool operator<(const vec3<T> &lhs, const vec3<T> &rhs) {
    return lhs.x_ < rhs.x_ && lhs.y_ < rhs.y_ && lhs.z_ < rhs.z_;
  }

  friend bool operator<=(const vec3<T> &lhs, const vec3<T> &rhs) {
    return lhs.x_ <= rhs.x_ && lhs.y_ <= rhs.y_ && lhs.z_ <= rhs.z_;
  }

  friend bool operator>(const vec3<T> &lhs, const vec3<T> &rhs) {
    return lhs.x_ > rhs.x_ && lhs.y_ > rhs.y_ && lhs.z_ > rhs.z_;
  }

  friend bool operator>=(const vec3<T> &lhs, const vec3<T> &rhs) {
    return lhs.x_ >= rhs.x_ && lhs.y_ >= rhs.y_ && lhs.z_ >= rhs.z_;
  }

  friend vec3<T> operator+(const vec3<T> &lhs, const vec3<T> &rhs) {
    return vec3<T>(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_);
  }

  friend vec3<T> operator-(const vec3<T> &lhs, const vec3<T> &rhs) {
    return vec3<T>(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
  }

  friend vec3<T> operator*(const vec3<T> &lhs, const vec3<T> &rhs) {
    return vec3<T>(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_, lhs.z_ * rhs.z_);
  }

  friend vec3<T> operator*(const T &lhs, const vec3<T> &rhs) {
    return vec3<T>(lhs * rhs.x_, lhs * rhs.y_, lhs + rhs.z_);
  }

  friend vec3<T> operator*(const vec3<T> &lhs, const T &rhs) {
    return vec3<T>(lhs.x_ * rhs, lhs.y_ * rhs, lhs.z_ + rhs);
  }

  friend vec3<T> operator/(const vec3<T> &lhs, const vec3<T> &rhs) {
    return vec3<T>(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_, lhs.z_ / rhs.z_);
  }

  friend vec3<T> operator/(const vec3<T> &lhs, const T &rhs) {
    return vec3<T>(lhs.x_ / rhs, lhs.y_ / rhs, lhs.z_ / rhs);
  }

  vec3<T> &operator+=(const vec3<T> &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;

    return *this;
  }

  vec3<T> &operator+=(const T &rhs) {
    x_ += rhs;
    y_ += rhs;
    z_ += rhs;

    return *this;
  }

  vec3<T> &operator-=(const vec3<T> &rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;

    return *this;
  }

  vec3<T> &operator-=(const T &rhs) {
    x_ -= rhs;
    y_ -= rhs;
    z_ -= rhs;

    return *this;
  }

  vec3<T> &operator*=(const vec3<T> &rhs) {
    x_ *= rhs.x_;
    y_ *= rhs.y_;
    z_ *= rhs.z_;

    return *this;
  }

  vec3<T> &operator*=(const T &rhs) {
    x_ *= rhs;
    y_ *= rhs;
    z_ *= rhs;

    return *this;
  }

  vec3<T> &operator/=(const vec3<T> &rhs) {
    x_ /= rhs.x_;
    y_ /= rhs.y_;
    z_ /= rhs.z_;

    return *this;
  }

  vec3<T> &operator/=(const T &rhs) {
    x_ /= rhs;
    y_ /= rhs;
    z_ /= rhs;

    return *this;
  }

  friend std::istream &operator>>(std::istream &stream, vec3<T> &rhs) {
    return stream >> rhs.x_ >> rhs.y_ >> rhs.z_;
  }

  friend std::wistream &operator>>(std::wistream &stream, vec3<T> &rhs) {
    return stream >> rhs.x_ >> rhs.y_ >> rhs.z_;
  }

  friend std::ostream &operator<<(std::ostream &stream, const vec3<T> &rhs) {
    return stream << rhs.x_ << " " << rhs.y_ << " " << rhs.z_;
  }

  friend std::wostream &operator<<(std::wostream &stream, const vec3<T> &rhs) {
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
