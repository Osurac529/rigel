#pragma once

#include <filesystem>

#include "rigel/image/image2d_fwd.hpp"

namespace rigel::image {

struct ImageExporter {
  struct Options {
    // if the format supports binary use it
    bool binary = true;
  };

  ImageExporter() = delete;

  static void
  Export(const Image2DRGB8 &image, const std::filesystem::path &path, const Options &options = {});

    static void
  Export(const Image2DRGBA8 &image, const std::filesystem::path &path, const Options &options = {});
};

} // namespace rigel::image
