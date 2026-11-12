#pragma once

#include <cstdint>
#include <functional>
#include <string>

#if defined(_WIN32)
#include <windows.h>
using WindowHandle = HWND;
#elif defined(__linux__)
#include <xcb/xcb.h>
using WindowHandle = xcb_window_t;
#else
#error "Unknown platform."
#endif


namespace rigel::graphics {
class Window {
public:
  Window(std::string const &title, std::uint32_t const width, std::uint32_t const height);

  ~Window();

  WindowHandle GetHandle() const;

  void SetOnDestroy(std::function<void()> onDestroy);

  std::uint32_t GetWidth() const;

  std::uint32_t GetHeight() const;

  HINSTANCE GetApplicationInstance() const;

private:
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  std::uint32_t width;
  std::uint32_t height;
  WindowHandle window;
  std::function<void()> onDestroy;
};

} // namespace rigel::graphics
