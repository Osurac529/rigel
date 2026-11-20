#include "rigel/image/convert.hpp"

namespace rigel::image {

Image2DRGBA8 Convert(const Image2DRGB8 &image, const Image2DRGB8::Type alpha) {
  Image2DRGBA8 converted(image.width(), image.height());

  image.Visit(
      [&converted, &alpha](
          const std::uint32_t x, const std::uint32_t y, const Image2DRGB8::Pixel &pixel) -> bool {
        converted.Set(x, y, Image2DRGBA8::Pixel(pixel, alpha));

        return false;
      });

  return converted;
}

} // namespace rigel::image
