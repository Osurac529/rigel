#pragma once

#include <cstdint>

namespace rigel::image {

template <typename T, const std::uint32_t NumChannels> class Image2D;
using Image2DRGB8 = Image2D<std::uint8_t, 3>;
using Image2DRGBA8 = Image2D<std::uint8_t, 4>;
using Image2DRG8 = Image2D<std::uint8_t, 2>;
using Image2DGrey8 = Image2D<std::uint8_t, 1>;
using Image2DGrey8F = Image2D<float, 1>;

} // namespace rigel::image
