#include "rigel/image/exception.hpp"

namespace rigel::image {

Exception::Exception(std::string message) : message_(std::move(message)) {}

const char *Exception::what() const {
  return message_.c_str();
}

} // namespace rigel::image
