#include "utilities/string.hpp"

namespace rigel::utilities {

std::wstring Widen(const std::string &narrow) {
  if (narrow.empty())
    return L"";

  // Determine the size required for the wide string
  size_t charsConverted = 0;
  mbstowcs_s(&charsConverted, nullptr, 0, narrow.c_str(), _TRUNCATE);

  std::wstring wide(charsConverted, L'\0');
  mbstowcs_s(&charsConverted, &wide[0], charsConverted, narrow.c_str(), _TRUNCATE);

  // Trim the trailing null character added by the system size calculation
  if (!wide.empty() && wide.back() == L'\0') {
    wide.pop_back();
  }

  return wide;
}

} // namespace rigel::utilities
