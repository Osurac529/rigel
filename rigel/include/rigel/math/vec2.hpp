#pragma once

#include <cmath>
#include <cstdint>
#include <istream>
#include <ostream>

namespace rigel::math {

// column vector
template <typename T> class vec2 {
public:
  explicit vec2() : x_(0), y_(0) {}

  explicit vec2(const T x, const T y) : x_(x), y_(y) {}

  const T &operator[](const std::int32_t index) const { return &x_[index]; }

  const T &x() const { return x_; }

  const T &r() const { return x_; }

  const T &y() const { return y_; }

  const T &g() const { return y_; }

  const T *data() const { return &x_; }

  std::size_t size() const { return 2; }

  T LengthSquared() const { return x_ * x_ + y_ * y_; }

  T Length() const { return std::sqrt(LengthSquared()); }

  T Dot(const vec2<T> &vec) const { return x_ * vec.x_ + y_ * vec.y_; }

  T Cross(const vec2<T> &rhs) const { return x_ * rhs.y_ - y_ * rhs.x_; }

  vec2<T> Normalized() const { return *this / Length(); }

  T &operator[](const int index) { return &x_[index]; }

  T &x() { return x_; }

  T &r() { return x_; }

  T &y() { return y_; }

  T &g() { return y_; }

  vec2<T> &Normalize() {
    const T length = Length();
    x_ /= length;
    y_ /= length;

    return *this;
  }

  vec2<T> &operator++() {
    ++x_;
    ++y_;

    return *this;
  }

  vec2<T> &operator++(std::int32_t) {
    ++x_;
    ++y_;

    return *this;
  }

  vec2<T> &operator--() {
    --x_;
    --y_;

    return *this;
  }

  vec2<T> &operator--(std::int32_t) {
    --x_;
    --y_;

    return *this;
  }

  friend bool operator==(const vec2<T> &lhs, const vec2<T> &rhs) {
    return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
  }

  friend bool operator!=(const vec2<T> &lhs, const vec2<T> &rhs) {
    return lhs.x_ != rhs.x_ || lhs.y_ != rhs.y_;
  }

  friend bool operator<(const vec2<T> &lhs, const vec2<T> &rhs) {
    return lhs.x_ < rhs.x_ && lhs.y_ < rhs.y_;
  }

  friend bool operator<=(const vec2<T> &lhs, const vec2<T> &rhs) {
    return lhs.x_ <= rhs.x_ && lhs.y_ <= rhs.y_;
  }

  friend bool operator>(const vec2<T> &lhs, const vec2<T> &rhs) {
    return lhs.x_ > rhs.x_ && lhs.y_ > rhs.y_;
  }

  friend bool operator>=(const vec2<T> &lhs, const vec2<T> &rhs) {
    return lhs.x_ >= rhs.x_ && lhs.y_ >= rhs.y_;
  }

  friend vec2<T> operator+(const vec2<T> &lhs, const vec2<T> &rhs) {
    return vec2<T>(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
  }

  friend vec2<T> operator-(const vec2<T> &lhs, const vec2<T> &rhs) {
    return vec2<T>(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
  }

  friend vec2<T> operator*(const vec2<T> &lhs, const vec2<T> &rhs) {
    return vec2<T>(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_);
  }

  friend vec2<T> operator*(const T &lhs, const vec2<T> &rhs) {
    return vec2<T>(lhs * rhs.x_, lhs * rhs.y_);
  }

  friend vec2<T> operator*(const vec2<T> &lhs, const T &rhs) {
    return vec2<T>(lhs.x_ * rhs, lhs.y_ * rhs);
  }

  friend vec2<T> operator/(const vec2<T> &lhs, const vec2<T> &rhs) {
    return vec2<T>(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_);
  }

  friend vec2<T> operator/(const vec2<T> &lhs, const T &rhs) {
    return vec2<T>(lhs.x_ / rhs, lhs.y_ / rhs);
  }

  vec2<T> &operator+=(const vec2<T> &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;

    return *this;
  }

  vec2<T> &operator+=(const T &rhs) {
    x_ += rhs;
    y_ += rhs;

    return *this;
  }

  vec2<T> &operator-=(const vec2<T> &rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;

    return *this;
  }

  vec2<T> &operator-=(const T &rhs) {
    x_ -= rhs;
    y_ -= rhs;

    return *this;
  }

  vec2<T> &operator*=(const vec2<T> &rhs) {
    x_ *= rhs.x_;
    y_ *= rhs.y_;

    return *this;
  }

  vec2<T> &operator*=(const T &rhs) {
    x_ *= rhs;
    y_ *= rhs;

    return *this;
  }

  vec2<T> &operator/=(const vec2<T> &rhs) {
    x_ /= rhs.x_;
    y_ /= rhs.y_;

    return *this;
  }

  vec2<T> &operator/=(const T &rhs) {
    x_ /= rhs;
    y_ /= rhs;

    return *this;
  }

  friend std::istream &operator>>(std::istream &stream, vec2<T> &rhs) {
    return stream >> rhs.x_ >> rhs.y_;
  }

  friend std::wistream &operator>>(std::wistream &stream, vec2<T> &rhs) {
    return stream >> rhs.x_ >> rhs.y_;
  }

  friend std::ostream &operator<<(std::ostream &stream, const vec2<T> &rhs) {
    return stream << rhs.x_ << " " << rhs.y_;
  }

  friend std::wostream &operator<<(std::wostream &stream, const vec2<T> &rhs) {
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
