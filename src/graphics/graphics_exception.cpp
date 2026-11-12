#include "graphics/graphics_exception.hpp"

namespace rigel::graphics {

GraphicsException::GraphicsException(std::string message) : message_(std::move(message)) {}

const char *GraphicsException::what() const {
  return message_.c_str();
}

} // namespace rigel::graphics
