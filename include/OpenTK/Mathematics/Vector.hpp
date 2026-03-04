#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <type_traits>
namespace OpenTK::Mathematics {
template <size_t N, typename T = float> struct Vector {
  static_assert(std::is_arithmetic<T>::value, "Vector must be numeric");
  static_assert(N > 0, "Vector size must be a non-zero positive integer");

  std::array<T, N> data;

  Vector() { data.fill(static_cast<T>(0)); }
  explicit Vector(T value) { data.fill(value); }

  // For specific values: Vector<2>(x,y)
  template <typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
  Vector(Args... args) : data{static_cast<T>(args)...} {}

  T &operator[](size_t idx) { return data[idx]; }
  const T &operator[](size_t idx) const { return data[idx]; }

  T &X() {
    static_assert(N >= 1, "Vector has no X component");
    return data[0];
  }
  T &Y() {
    static_assert(N >= 1, "Vector has no Y component");
    return data[1];
  }
  T &Z() {
    static_assert(N >= 1, "Vector has no Z component");
    return data[2];
  }
  T &W() {
    static_assert(N >= 1, "Vector has no W component");
    return data[3];
  }

  Vector operator+(const Vector &other) const {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = data[i] + other[i];
    return result;
  }
  Vector operator-(const Vector &other) const {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = data[i] - other[i];
    return result;
  }
  Vector operator*(T scalar) const {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = data[i] * scalar;
    return result;
  }
  Vector operator/(T scalar) const {
    assert(scalar != 0);
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = data[i] / scalar;
    return result;
  }
  T length_squared() const {
    T sum = 0;
    for (const auto &val : data)
      sum += val * val;
    return sum;
  }
  T length() const { return std::sqrt(static_cast<T>(length_squared())); }
  void normalize() {
    float len = length();
    if (len > 1e-6f) {
      for (size_t i = 0; i < N; ++i)
        data[i] = static_cast<T>(data[i] / len);
    }
  }
  static T dot(const Vector &a, const Vector &b) {
    T result = 0;
    for (size_t i = 0; i < N; ++i)
      result += a[i] * b[i];
    return result;
  }
  static Vector lerp(const Vector &a, const Vector &b, float blend) {
    Vector result;
    for (size_t i = 0; i < N; ++i) {
      result[i] = static_cast<T>(a[i] + (b[i] - a[i]) * blend);
    }
    return result;
  }

  friend std::ostream &operator<<(std::ostream &os, const Vector<N, T> v) {
    os << "(";
    for (size_t n = 0; n < N; n++) {
      os << v.data[n];
      if (n != N - 1)
        os << ", ";
    }
    os << ")";
    return os;
  }

  static Vector component_min(const Vector &a, const Vector &b) {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = std::min(a[i], b[i]);
    return result;
  }
  static Vector component_max(const Vector &a, const Vector &b) {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = std::max(a[i], b[i]);
    return result;
  }

  static Vector zero() { return Vector(static_cast<T>(0)); }
  static Vector one() { return Vector(static_cast<T>(1)); }
};
/*
 *  Standard Vectors
 * */
using Vector2 = Vector<2, float>;
using Vector3 = Vector<3, float>;
using Vector4 = Vector<4, float>;
using Vector2b = Vector<2, bool>;
using Vector3b = Vector<3, bool>;
using Vector4b = Vector<4, bool>;
using Vector2d = Vector<2, double>;
using Vector3d = Vector<3, double>;
using Vector4d = Vector<4, double>;
using Vector2i = Vector<2, int>;
using Vector3i = Vector<3, int>;
using Vector4i = Vector<4, int>;

} // namespace OpenTK::Mathematics
