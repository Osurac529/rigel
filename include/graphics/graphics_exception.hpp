#pragma once

#include <exception>
#include <string>

namespace rigel::graphics {

class GraphicsException : public std::exception {
public:
  explicit GraphicsException(std::string message);

  const char *what() const override;

private:
  std::string message_;
};

} // namespace rigel::graphics
