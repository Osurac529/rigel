#pragma once

#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

template <typename T, void (*AddRefFunction)(T), void (*ReleaseFunction)(T)> class WGPUObject {
public:
  explicit WGPUObject(T object) : object_(object) {
    if (!object_) {
      throw GraphicsException("Failed to create object.");
    }
  }

  WGPUObject(const WGPUObject &other) : object_(other.object_) { AddRefFunction(object_); }

  WGPUObject &operator=(const WGPUObject &other) {
    if (this != &other) {
      ReleaseFunction(object_);
      object_ = other.object_;
      AddRefFunction(object_);
    }

    return *this;
  }

  WGPUObject(WGPUObject &&other) noexcept : object_(other.object_) { other.object_ = nullptr; }

  WGPUObject &operator=(WGPUObject &&other) noexcept {
    if (this != &other) {
      object_ = other.object_;
      other.object_ = nullptr;
    }

    return *this;
  }

  virtual ~WGPUObject() {
    if (object_) {
      ReleaseFunction(object_);
    }
  }

  const T &native() const { return object_; }

private:
  T object_;
};

} // namespace rigel::graphics
