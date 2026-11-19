#pragma once

#include <filesystem>

#include "rigel/image/image2d.hpp"

namespace rigel::image {

enum class PPMFormat { ASCII, BINARY };

void ExportPPM(
    const Image2DRGB8 &image,
    const std::filesystem::path &path,
    PPMFormat format = PPMFormat::ASCII);

} // namespace rigel::image
