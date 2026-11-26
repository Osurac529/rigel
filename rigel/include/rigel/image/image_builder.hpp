#pragma once

#include <cstdint>

#include "rigel/image/image2d_fwd.hpp"

namespace rigel::image {

struct ImageBuilder {
  ImageBuilder() = delete;

  static Image2DRGB8
  BuildCheckerBoard(std::uint32_t width, std::uint32_t height, std::uint32_t cell_size);

  static Image2DRGBA8 BuildCheckerBoardWithAlpha(
      std::uint32_t width,
      std::uint32_t height,
      std::uint32_t cell_size,
      std::uint8_t alpha = 255);
};

} // namespace rigel::image
