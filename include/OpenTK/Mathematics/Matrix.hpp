#pragma once

#include "OpenTK/Mathematics/Vector.hpp"
#include <concepts>
#include <cstddef>
#include <type_traits>
namespace OpenTK::Mathematics {
/*
 * Jesus christ i hate porting this class ong;
 * */
template <size_t R, size_t C, typename T = float> struct Matrix {
public:
  static_assert(std::is_arithmetic<T>::value, "Matrix must be numeric");
  static_assert(R > 0, "Matrix width must be a non-zero positive integer");
  static_assert(C > 0, "Matrix height must be a non-zero positive integer");

  std::array<Vector<C, T>, R> data{};

  Matrix() { data.fill(Vector<R, T>()); }
};
} // namespace OpenTK::Mathematics
