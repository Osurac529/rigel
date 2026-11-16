#pragma once

#include "webgpu/exception.hpp"

namespace webgpu {

template <typename T, void (*AddRefFunction)(T), void (*ReleaseFunction)(T)> class Object {
public:
  explicit Object(T object) : object_(object) {
    if (!object_) {
      throw Exception("Failed to create object.");
    }
  }

  Object(const Object &other) : object_(other.object_) { AddRefFunction(object_); }

  Object &operator=(const Object &other) {
    if (this != &other) {
      ReleaseFunction(object_);
      object_ = other.object_;
      AddRefFunction(object_);
    }

    return *this;
  }

  Object(Object &&other) noexcept : object_(other.object_) { other.object_ = nullptr; }

  Object &operator=(Object &&other) noexcept {
    if (this != &other) {
      object_ = other.object_;
      other.object_ = nullptr;
    }

    return *this;
  }

  virtual ~Object() {
    if (object_) {
      ReleaseFunction(object_);
    }
  }

  T &handle() { return object_; }

  const T &handle() const { return object_; }

private:
  T object_;
};

} // namespace webgpu
