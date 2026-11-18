#pragma once

#include "webgpu/exception.hpp"

namespace webgpu {

template <typename T, void (*AddRefFunction)(T), void (*ReleaseFunction)(T)> class Object {
public:
  Object() : object_(nullptr) {}

  explicit Object(const T& object) : object_(object) {
    if (!object_) {
      throw Exception("Failed to create object.");
    }
  }

  Object(const Object &other) : object_(other.object_) { AddReference(); }

  Object &operator=(const Object &other) {
    if (this != &other) {
      Release();
      object_ = other.object_;
      AddReference();
    }

    return *this;
  }

  Object(Object &&other) noexcept : object_(other.object_) { other.object_ = nullptr; }

  Object &operator=(Object &&other) noexcept {
    if (this != &other) {
      Release();
      object_ = other.object_;
      other.object_ = nullptr;
    }

    return *this;
  }

  virtual ~Object() { Release(); }

  T &handle() { return object_; }

  const T &handle() const { return object_; }

  explicit operator bool() const { return object_ != nullptr; }

private:
  void AddReference() {
    if (object_) {
      AddRefFunction(object_);
    }
  }

  void Release() {
    if (object_) {
      ReleaseFunction(object_);
    }
  }

  T object_;
};

} // namespace webgpu
