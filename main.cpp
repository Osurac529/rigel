#include <iostream>

#include "graphics/graphics.hpp"

int main() {
  try {
    rigel::graphics::Application application;

    application.Run([](const int key, const float , const float ) {
      std::cout << key << std::endl;
    });
  } catch (const std::exception &exception) {
    std::cout << "Exception: " << exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
