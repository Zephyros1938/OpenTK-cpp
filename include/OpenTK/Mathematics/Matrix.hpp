#pragma once

#include "OpenTK/Mathematics/Vector.hpp"
#include <concepts>
#include <cstddef>
#include <type_traits>
namespace OpenTK::Mathematics {
template <size_t R, size_t C, typename T = float> struct Matrix {
  static_assert(std::is_arithmetic<T>::value, "Matrix must be numeric");
  static_assert(R > 0, "Matrix width must be a non-zero positive integer");
  static_assert(C > 0, "Matrix height must be a non-zero positive integer");

  std::array<Vector<C, T>, R> data{};

  Matrix() { data.fill(Vector<R, T>()); }
  explicit Matrix(T value) { data.fill(Vector<R, T>(value)); }
  template <typename... Args,
            typename = std::enable_if<sizeof...(Args) == C * R>>
  Matrix(Args... args) {
    T values[] = {static_cast<T>(args)...};
    for (size_t i = 0; i < R; ++i) {
      for (size_t j = 0; j < C; ++j) {
        data[i][j] = values[i * C + j];
      }
    }
  }
  template <typename... Args>
    requires(sizeof...(Args) == C && (std::same_as<Args, Vector<C, T>> && ...))
  Matrix(Args... args) : data{args...} {};

  constexpr T Determinant()
    requires(R == C)
  {
    if constexpr (R == 1) {
      return data[0][0];
    } else if constexpr (R == 2) {
      return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    } else if constexpr (R == 3) {
      return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) -
             data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
             data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    } else {
      T det = 0;
      int sign = 1;
      for (size_t j = 0; j < C; ++j) {
        Matrix<R - 1, C - 1, T> sub;

        // Fill submatrix
        for (size_t i = 1; i < R; ++i) { // Start from row 1 to skip row 0
          size_t subCol = 0;
          for (size_t k = 0; k < C; ++k) {
            if (k == j)
              continue; // Skip current column
            sub.data[i - 1][subCol] = data[i][k];
            subCol++;
          }
        }

        det += sign * data[0][j] * sub.Determinant();
        sign = -sign;
      }
      return det;
    }
  }

  static constexpr Matrix Identity() {
    Matrix res{};
    constexpr size_t minDim = (R < C) ? R : C;
    for (size_t i = 0; i < minDim; ++i)
      res.data[i][i] = static_cast<T>(1);
    return res;
  }
  static constexpr Matrix Zero() {
    Matrix res{};
    for (size_t i = 0; i < R; ++i) {
      res.data[R] = Vector<C, T>();
    }
    return res;
  }

  friend std::ostream &operator<<(std::ostream &os, const Matrix<R, C, T> m) {
    os << "{ ";
    for (size_t n = 0; n < R; ++n) {
      os << m.data[n];
      if (n <= R - 2) {
        os << ", ";
      }
    }
    os << " }";
    return os;
  }
};
} // namespace OpenTK::Mathematics
