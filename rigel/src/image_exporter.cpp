#include "rigel/image/image_exporter.hpp"

#include <iostream>

#include "ppm_exporter.hpp"
#include "rigel/image/exception.hpp"

namespace rigel::image {

void ImageExporter::Export(
    const Image2DRGB8 &image,
    const std::filesystem::path &path,
    const Options &options) {
  const auto extension = path.extension().generic_string();

  if (".ppm" == extension) {
    ExportPPM(image, path, options.binary ? PPMFormat::BINARY : PPMFormat::ASCII);
  } else {
    throw Exception("No exporter for image extension: " + extension);
  }
}

void ImageExporter::Export(
    const Image2DRGBA8 &,
    const std::filesystem::path &path,
    const Options &) {
  const auto extension = path.extension().generic_string();

  if (".ppm" == extension) {
    std::cout << "ppm does not support RGBA" << std::endl;
  } else {
    throw Exception("No exporter for image extension: " + extension);
  }
}

} // namespace rigel::image
