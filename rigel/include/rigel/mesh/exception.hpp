#pragma once

#include <exception>
#include <string>

namespace rigel::mesh {

class Exception : public std::exception {
public:
  explicit Exception(std::string message);

  const char *what() const override;

private:
  std::string message_;
};

} // namespace rigel::mesh
