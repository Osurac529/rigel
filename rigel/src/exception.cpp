#include "rigel/mesh/exception.hpp"

namespace rigel::mesh {

Exception::Exception(std::string message) : message_(std::move(message)) {}

const char *Exception::what() const {
  return message_.c_str();
}

} // namespace rigel::mesh
