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

  Matrix() = default;

  T &operator[](size_t x, size_t y) { return data[x][y]; }
  const T &operator[](size_t x, size_t y) const { return data[x][y]; }

  constexpr static Matrix Identity()
    requires(R == C)
  {
    Matrix<R, C, T> m{};
    for (size_t i = 0; i < R; i++) {
      m.data[i][i] = 1;
    }
    return m;
  }

  template <typename... Rows>
  Matrix FromRows(Rows... rows)
    requires(sizeof...(Rows) == R) &&
            (std::convertible_to<Rows, Vector<C, T>> && ...)
  {
    Matrix<R, C, T> m;
    m.data = {static_cast<Vector<C, T>>(rows)...};
    return m;
  }

  template <typename... Args>
  Matrix(Args... args)
    requires(sizeof...(Args) == R * C) && (std::same_as<Args, T> && ...)
  {
    T values[] = {static_cast<T>(args)...};

    for (size_t i = 0; i < R; i++) {
      for (size_t j = 0; j < C; j++) {
        data[i][j] = values[i * C + j];
      }
    }
  }
  Matrix(Matrix<R - 1, C - 1, T> topLeft)
    requires(R > 1 && C > 1 && R == C)
  {
    data = Identity();
    for (size_t i = 0; i < R - 1; i++) {
      for (size_t j = 0; j < C - 1; j++) {
        data[i][j] = topLeft.data[i][j];
      }
    }
  }
  constexpr Matrix<R - 1, C - 1, T> GetMinor(size_t row, size_t col) const {
    Matrix<R - 1, C - 1, T> result;
    size_t r_out = 0;
    for (size_t r = 0; r < R; ++r) {
      if (r == row)
        continue;
      size_t c_out = 0;
      for (size_t c = 0; c < C; ++c) {
        if (c == col)
          continue;
        result.data[r_out][c_out] = data[r][c];
        c_out++;
      }
      r_out++;
    }
    return result;
  }

  constexpr T Determinant() const
    requires(R == C)
  {
    if constexpr (R == 1) {
      return data[0][0];
    } else if constexpr (R == 2) {
      return (data[0][0] * data[1][1]) - (data[0][1] * data[1][0]);
    } else {
      T det = 0;
      int sign = 1;
      for (size_t i = 0; i < C; ++i) {
        // Laplace expansion along the first row
        det += sign * data[0][i] * GetMinor(0, i).Determinant();
        sign = -sign;
      }
      return det;
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix m) {
    os << "{ ";
    for (size_t i = 0; i < R; ++i)
      os << m.data[i] << (i == R - 1 ? "" : ", ");
    os << " }";
    return os;
  }
};
} // namespace OpenTK::Mathematics
