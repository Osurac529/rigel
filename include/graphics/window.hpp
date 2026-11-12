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
  Window(const std::string &title, const std::uint32_t width, std::uint32_t height);

  ~Window();

  WindowHandle GetHandle() const;

  HINSTANCE GetApplicationInstance() const;

  std::uint32_t GetWidth() const;

  std::uint32_t GetHeight() const;

  void SetOnDestroy(std::function<void()> on_destroy);

  void SetOnResize(std::function<void(std::uint32_t, std::uint32_t)> on_resize);

private:
  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  std::uint32_t width_;
  std::uint32_t height_;
  WindowHandle window_;
  std::function<void()> on_destroy_;
  std::function<void(std::uint32_t, std::uint32_t)> on_resize_;
};

} // namespace rigel::graphics
