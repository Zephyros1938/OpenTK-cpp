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
  template <size_t Rr, size_t Cc>
  Matrix(Matrix<Rr, Cc, T> topLeft)
    requires(Rr >= 2 && Cc >= 2 && Rr == Cc && Rr == R - 1 && Cc == C - 1)
  {
    for (size_t row = 0; row < Rr; ++row) {
      for (size_t col = 0; col < Cc; ++col) {
        data[row][col] = topLeft.data[row][col];
      }
      data[row][C - 1] = 0;
    }
    Vector<C, T> v{};
    v[C - 1] = 1;
    data[R - 1] = v;
  }

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

  constexpr Vector<R, T> GetRow(size_t row) const {
    return Vector<R, T>{data[row]};
  }
  constexpr void SetRow(size_t rowIdx, Vector<R, T> row) const {
    data[rowIdx] = row;
  }
  constexpr Vector<C, T> GetColumn(size_t col) const {
    Vector<C, T> dataRet{};
    for (size_t row = 0; row < R; ++row) {
      dataRet[row] = T(data[row][col]);
    }
    return dataRet;
  }
  constexpr void SetColumn(size_t colIdx, Vector<C, T> col) const {
    for (size_t row = 0; row < R; ++row) {
      data[row][colIdx] = col[row];
    }
  }
  constexpr Vector<R, T> Diagonal() const
    requires(R == C)
  {
    Vector<R, T> outVec{};
    for (size_t l = 0; l < R; l++) {
      outVec[l] = data[l][l];
    }
    return outVec;
  }
  constexpr T Trace() const
    requires(R == C)
  {
    T outV;
    for (size_t l = 0; l < R; l++) {
      outV += data[l][l];
    }
    return outV;
  }
  constexpr void Invert() const { *this = Invert(*this); }
  constexpr Matrix<R, C, T> Inverted() const {
    Matrix<R, C, T> m = *this;
    if (m->Determinant() != 0)
      m->Invert();
    return m;
  }
  constexpr void Transpose() const { *this = Transpose(*this); }
  constexpr Matrix<R, C, T> Transposed() const {
    Matrix<R, C, T> m = *this;
    m.Transpose();
    return m;
  }
  constexpr void Normalize() const {
    auto determinant = Determinant();
    for (size_t row = 0; row < R; ++row) {
      data[row] /= determinant;
    }
  }
  constexpr Matrix<R, C, T> Normalized() const {
    Matrix<R, C, T> m = *this;
    m.Normalize();
    return m;
  }
  template <typename... Args>
    requires(sizeof...(Args) == R && (std::same_as<Args, Vector<R, T>> && ...))
  constexpr void Swizzle(Args... args) const {
    *this = Swizzle(*this, args...);
  }
  template <typename... Args>
    requires(sizeof...(Args) == R && (std::same_as<Args, Vector<R, T>> && ...))
  constexpr Matrix<R, C, T> Swizzled(Args... args) const {
    Matrix<R, C, T> m = *this;
    m.Swizzle(args...);
    return m;
  }

  constexpr Matrix<R, C, T> ClearTranslation() const
    requires(C == R, R == 4)
  {
    Matrix<R, C, T> m = *this;
    m.data[3].SetSubVectorI(Vector<3, T>::Zero(), std::array{0, 1, 2});
    return m;
  }
  constexpr Matrix<R, C, T> ClearScale() const
    requires(C == R, R == 4)
  {
    Matrix<R, C, T> m = *this;
    m.data[0].SetSubVector(m.data[0].GetSubVector(0, 1, 2).Normalized());
    m.data[1].SetSubVector(m.data[1].GetSubVector(0, 1, 2).Normalized());
    m.data[2].SetSubVector(m.data[2].GetSubVector(0, 1, 2).Normalized());
    return m;
  }
  constexpr Matrix<R, C, T> ClearRotation() const
    requires(C == R, R == 4)
  {
    Matrix<R, C, T> m = *this;
    m.data[0].SetSubVector(Vector<3, T>(m.data[0].Length(), 0, 0), 0, 1, 2);
    m.data[1].SetSubVector(Vector<3, T>(0, m.data[1].Length(), 0), 0, 1, 2);
    m.data[2].SetSubVector(Vector<3, T>(0, 0, m.data[2].Length()), 0, 1, 2);
    return m;
  }
  constexpr Vector<3, T> ExtractTranslation() const
    requires(C == R, R == 4)
  {
    return GetRow(3).GetSubVector(0, 1, 2);
  }
  constexpr Vector<3, T> ExtractScale() const
    requires(C == R, R == 4)
  {
    return Vector<3, T>{GetRow(0).GetSubVector(0, 1, 2).Length(),
                        GetRow(1).GetSubVector(0, 1, 2).Length(),
                        GetRow(2).GetSubVector(0, 1, 2).Length()};
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
  T operator[](size_t rid, size_t cid) {
    static_assert(0 < rid && rid < R && 0 < cid && cid < C,
                  std::format("You tried to access matrix<{}, {}> at [{}, {}]",
                              R, C, rid, cid));
    return data[rid][cid];
  }
  constexpr T operator[](size_t rid, size_t cid) const {
    static_assert(0 < rid && rid < R && 0 < cid && cid < C,
                  std::format("You tried to access matrix<{}, {}> at [{}, {}]",
                              R, C, rid, cid));
    return data[rid][cid];
  }
};
} // namespace OpenTK::Mathematics
