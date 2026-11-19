#pragma once

#include <array>
#include <cstdint>
#include <filesystem>
#include <vector>

#include "rigel/image/image_exporter.hpp"
#include "rigel/math/math.hpp"

namespace rigel::image {

template <typename T, const std::uint32_t NumChannels> class Image2D {
public:
  static_assert(NumChannels > 0);

  using Pixel = std::conditional_t<
      1 == NumChannels,
      T,
      std::conditional_t<
          2 == NumChannels,
          math::vec2<T>,
          std::conditional_t<
              3 == NumChannels,
              math::vec3<T>,
              std::conditional_t<4 == NumChannels, math::vec4<T>, std::array<T, NumChannels>>>>>;

  Image2D() = default;

  explicit Image2D(const std::uint32_t width, const std::uint32_t height) { Resize(width, height); }

  explicit Image2D(const std::uint32_t width, const std::uint32_t height, const Pixel &pixel) {
    Resize(width, height, pixel);
  }

  explicit Image2D(const std::filesystem::path &path) { Load(path); }

  void Set(const std::uint32_t x, std::uint32_t y, const Pixel &pixel) {
    data_[y * width_ + x] = pixel;
  }

  Pixel &Get(const std::uint32_t x, std::uint32_t y) { return data_[y * width_ + x]; }

  const Pixel &Get(const std::uint32_t x, std::uint32_t y) const { return data_[y * width_ + x]; }

  void Resize(const std::uint32_t width, const std::uint32_t height) {
    data_.resize(width * height);
    width_ = width;
    height_ = height;
  }

  void Resize(const std::uint32_t width, const std::uint32_t height, const Pixel &pixel) {
    data_.resize(static_cast<std::size_t>(width * height), pixel);
    width_ = width;
    height_ = height;
  }

  void Write(const std::filesystem::path &path, const ImageExporter::Options &options = {}) const {
    ImageExporter::Export(*this, path, options);
  }

  void Load(const std::filesystem::path &path) { // todo
  }

  const std::size_t BytesSize() const { return sizeof(Pixel) * width_ * height_; }

  const Pixel *data() const { return data_.data(); }

  std::size_t size() const { return data_.size(); }

  std::uint32_t width() const { return width_; }

  std::uint32_t height() const { return height_; }

  std::uint32_t channels() const { return NumChannels; }

private:
  std::uint32_t width_;
  std::uint32_t height_;
  std::vector<Pixel> data_;
};

} // namespace rigel::image

#include "rigel/image/image2d_fwd.hpp"
