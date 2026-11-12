#pragma once

namespace rigel::utilities {

class MoveOnly {
public:
  MoveOnly(const MoveOnly &) = delete;
  MoveOnly &operator=(const MoveOnly &) = delete;

  MoveOnly(MoveOnly &&) = default;
  MoveOnly &operator=(MoveOnly &&) = default;

protected:
  constexpr MoveOnly() = default;
  ~MoveOnly() = default;
};

} // namespace rigel::utilities
