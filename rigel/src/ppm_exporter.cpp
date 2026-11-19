#include "ppm_exporter.hpp"

#include <fstream>

#include "rigel/image/exception.hpp"

namespace rigel::image {

namespace {

void WriteASCII(const Image2DRGB8 &image, const std::filesystem::path &path) {
  std::ofstream stream(path);

  stream.exceptions(std::ofstream::badbit | std::ofstream::eofbit | std::ofstream::failbit);

  stream << "P3\n" << image.width() << " " << image.height() << "\n255\n";

  const auto *data_ptr = image.data();
  const auto num_channels = image.channels();
  const auto size = image.size();

  for (std::size_t i = 0; i < size; ++i) {
    for (std::size_t channel = 0; channel < num_channels; ++channel) {
      stream << static_cast<std::uint32_t>(data_ptr[i][channel]) << '\n';
    }
  }
}

void WriteBinary(const Image2DRGB8 &image, const std::filesystem::path &path) {
  std::ofstream stream(path, std::ofstream::binary);

  stream.exceptions(std::ofstream::badbit | std::ofstream::eofbit | std::ofstream::failbit);

  stream << "P6\n" << image.width() << " " << image.height() << "\n255\n";

  stream.write(reinterpret_cast<const char *>(image.data()), image.BytesSize());
}

} // namespace

void ExportPPM(
    const Image2DRGB8 &image,
    const std::filesystem::path &path,
    const PPMFormat format) {
  try {
    if (PPMFormat::ASCII == format) {
      WriteASCII(image, path);
    } else {
      WriteBinary(image, path);
    }
  } catch (const std::ofstream::failure &failure) {
    throw Exception("Failed to write: " + path.generic_string() + " :" + failure.what());
  }
}

} // namespace rigel::image
