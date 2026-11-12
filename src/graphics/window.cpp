#include "graphics/window.hpp"

#include <stdexcept>
#include <vector>

#include "utilities/string.hpp"

namespace rigel::graphics {

Window::Window(const std::string &title, const std::uint32_t width, const std::uint32_t height)
    : width_(width), height_(height) {
#if defined(_WIN32)
  WNDCLASSEX windowClass;
  memset(&windowClass, 0, sizeof(windowClass));
  windowClass.cbSize = sizeof(windowClass);
  windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
  windowClass.lpfnWndProc = WindowProc;
  windowClass.hInstance = GetModuleHandleW(nullptr);
  windowClass.lpszClassName = L"WindowClass";

  if (!::RegisterClassExW(&windowClass)) {
    throw std::runtime_error("Failed to register window class");
  }

  RECT rect;
  rect.top = 0;
  rect.bottom = height;
  rect.left = 0;
  rect.right = width;

  auto const style(WS_OVERLAPPEDWINDOW);

  if (!::AdjustWindowRect(&rect, style, false)) {
    throw std::runtime_error("AdjustWindowRect failed");
  }

  const std::wstring title_wide = utilities::Widen(title);

  if (nullptr == (window_ = ::CreateWindowExW(
                      0, windowClass.lpszClassName, title_wide.c_str(), style | WS_VISIBLE,
                      CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
                      nullptr, nullptr, windowClass.hInstance, nullptr))) {
    throw std::runtime_error("CreateWindowExW failed");
  }

  ::SetWindowLongPtrW(window_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

  ShowWindow(window_, SW_SHOW);
#elif defined(__linux__)

  connection = xcb_connect(nullptr, nullptr);

  if (xcb_connection_has_error(connection)) {
    throw std::runtime_error("Cannot open display");
  }

  // get the first screen
  auto s = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

  // create window
  window = xcb_generate_id(connection);
  auto mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  std::uint32_t values[2];
  values[0] = s->white_pixel;
  values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;
  xcb_create_window(
      connection, s->root_depth, window, s->root, 10, 10, width, height, 1,
      XCB_WINDOW_CLASS_INPUT_OUTPUT, s->root_visual, mask, values);

  xcb_change_property(
      connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8, title.size(),
      title.c_str());

  // map (show) the window
  xcb_map_window(connection, window);

  xcb_flush(connection);
#endif
}

Window::~Window() {
#if defined(_WIN32)
  DestroyWindow(window_);
#elif defined(__linux__)
  xcb_destroy_window(connection, window);
#endif
}

WindowHandle Window::GetHandle() const {
  return window_;
}

void Window::SetOnDestroy(std::function<void()> on_destroy) {
  on_destroy_ = on_destroy;
}

void Window::SetOnResize(std::function<void(std::uint32_t, std::uint32_t)> on_resize) {
  on_resize_ = std::move(on_resize);
}

std::uint32_t Window::GetWidth() const {
  return width_;
}

std::uint32_t Window::GetHeight() const {
  return height_;
}

#if defined(_WIN32)
HINSTANCE Window::GetApplicationInstance() const {
  return GetModuleHandleW(nullptr);
}
#elif defined(__linux__)
xcb_connection_t *Window::GetConnection() const {
  return connection;
}
#endif

#if defined(_WIN32)
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  auto *window = reinterpret_cast<Window *>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));

  switch (uMsg) {
  case WM_DESTROY: {
    if (window->on_destroy_) {
      window->on_destroy_();
    }

    ::PostQuitMessage(0);

    break;
  }

  case WM_SIZE: {
    RECT rect;

    if (window && window->on_resize_ && ::GetClientRect(hwnd, &rect)) {
      window->on_resize_(rect.right - rect.left, rect.bottom - rect.top);
    }

    break;
  }

  default: {
    break;
  }
  }

  // a pass-through for now. We will return to this callback
  return ::DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
#endif

} // namespace rigel::graphics
