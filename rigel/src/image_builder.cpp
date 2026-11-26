#include "rigel/image/image_builder.hpp"

#include "rigel/image/image2d.hpp"

namespace rigel::image {

Image2DRGB8 ImageBuilder::BuildCheckerBoard(
    const std::uint32_t width,
    const std::uint32_t height,
    const std::uint32_t cell_size) {
  const auto white = Image2DRGB8::Pixel(255, 255, 255);
  const auto black = Image2DRGB8::Pixel(0, 0, 0);
  Image2DRGB8 image(width, height);
  bool toggle = false;

  for (std::uint32_t y = 0; y < height; ++y) {
    if (0 == y % cell_size) {
      toggle = !toggle;
    }

    for (std::uint32_t x = 0; x < width; ++x) {
      if (0 == x % cell_size) {
        toggle = !toggle;
      }

      if (toggle) {
        image.Set(x, y, white);
      } else {
        image.Set(x, y, black);
      }
    }
  }

  return image;
}

Image2DRGBA8 ImageBuilder::BuildCheckerBoardWithAlpha(
    std::uint32_t width,
    std::uint32_t height,
    std::uint32_t cell_size,
    std::uint8_t alpha) {
  const auto white = Image2DRGBA8::Pixel(255, 255, 255, alpha);
  const auto black = Image2DRGBA8::Pixel(0, 0, 0, alpha);
  Image2DRGBA8 image(width, height);
  bool toggle = false;

  for (std::uint32_t y = 0; y < height; ++y) {
    if (0 == y % cell_size) {
      toggle = !toggle;
    }

    for (std::uint32_t x = 0; x < width; ++x) {
      if (0 == x % cell_size) {
        toggle = !toggle;
      }

      if (toggle) {
        image.Set(x, y, white);
      } else {
        image.Set(x, y, black);
      }
    }
  }

  return image;
}

} // namespace rigel::image
