#pragma once

#include <type_traits>

namespace core {
namespace enumutil {
template <typename E> constexpr bool HasFlag(E value, E flag) {
  static_assert(std::is_enum<E>::value, "HasFlag only works with enum types.");

  // Convert to underlying type (int, uint32_t, etc.) to allow bitwise &
  using T = typename std::underlying_type<E>::type;
  return (static_cast<T>(value) & static_cast<T>(flag)) == static_cast<T>(flag);
}
} // namespace enumutil
} // namespace core
