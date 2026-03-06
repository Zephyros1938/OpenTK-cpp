#pragma once

#include <array>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <ostream>
#include <type_traits>
#include <vector>
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
  template <typename... Args>
    requires(sizeof...(Args) > 0) &&
            (std::is_convertible_v<Args, std::size_t> && ...)
  Vector<sizeof...(Args), T> GetSubVector(Args... args) const {
    return Vector<sizeof...(Args), T>{data[args]...};
  }
  template <typename... Args>
    requires(sizeof...(Args) > 0 && sizeof...(Args) < N &&
             (std::is_convertible_v<Args, std::size_t> && ...))
  constexpr void SetSubVector(Vector<sizeof...(Args), T> subVec,
                              Args... indixes) {
    size_t i = 0;
    ((data[indixes] = subVec[i++]), ...);
  }
  template <size_t S, typename R>
    requires(S > 0 && S < N && std::ranges::random_access_range<R> &&
             std::convertible_to<std::ranges::range_value_t<R>, size_t>)
  constexpr void SetSubVectorI(Vector<S, T> subVec, R indices) {
    for (size_t i = 0; i < S; ++i) {
      data[indices[i]] = subVec[i];
    }
  }

  constexpr T &X() const {
    static_assert(N >= 1, "Vector has no X component");
    return data[0];
  }
  constexpr T &Y() const {
    static_assert(N >= 1, "Vector has no Y component");
    return data[1];
  }
  constexpr T &Z() const {
    static_assert(N >= 1, "Vector has no Z component");
    return data[2];
  }
  constexpr T &W() const {
    static_assert(N >= 1, "Vector has no W component");
    return data[3];
  }

  constexpr Vector operator+(const Vector &other) const {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = data[i] + other[i];
    return result;
  }
  constexpr Vector operator-(const Vector &other) const {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = data[i] - other[i];
    return result;
  }
  constexpr Vector operator*(T scalar) const {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = data[i] * scalar;
    return result;
  }
  constexpr Vector operator/(T scalar) const {
    assert(scalar != 0);
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = data[i] / scalar;
    return result;
  }
  constexpr void operator+=(const Vector &other) const { this = this + other; }
  constexpr void operator-=(const Vector &other) const { this = this - other; }
  constexpr void operator*=(const Vector &other) const { this = this * other; }
  constexpr void operator/=(const Vector &other) const { this = this / other; }

  constexpr T LengthSquared() const {
    T sum = 0;
    for (const auto &val : data)
      sum += val * val;
    return sum;
  }
  constexpr T Length() const {
    return std::sqrt(static_cast<T>(LengthSquared()));
  }
  constexpr void Normalize() const {
    float len = Length();
    if (len > 1e-6f) {
      for (size_t i = 0; i < N; ++i)
        data[i] = static_cast<T>(data[i] / len);
    }
  }
  constexpr T Dot(const Vector &a, const Vector &b) const {
    T result = 0;
    for (size_t i = 0; i < N; ++i)
      result += a[i] * b[i];
    return result;
  }
  constexpr Vector Lerp(const Vector &a, const Vector &b, float blend) const {
    Vector result;
    for (size_t i = 0; i < N; ++i) {
      result[i] = static_cast<T>(a[i] + (b[i] - a[i]) * blend);
    }
    return result;
  }

  constexpr int SizeInBytes() const { return sizeof(this); }

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

  constexpr Vector ComponentMin(const Vector &a, const Vector &b) const {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = std::min(a[i], b[i]);
    return result;
  }
  constexpr Vector ComponentMax(const Vector &a, const Vector &b) const {
    Vector result;
    for (size_t i = 0; i < N; ++i)
      result[i] = std::max(a[i], b[i]);
    return result;
  }

  static Vector Zero() { return Vector(static_cast<T>(0)); }
  static Vector One() { return Vector(static_cast<T>(1)); }
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
