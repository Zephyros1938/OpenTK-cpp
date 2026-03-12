#pragma once

#include "OpenTK/Mathematics/Enums/MidpointRounding.hpp"
#include "OpenTK/Mathematics/MathHelper.hpp"
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
  constexpr static Vector Zero() { return Vector(static_cast<T>(0)); }
  constexpr static Vector One() { return Vector(static_cast<T>(1)); }
  static int SizeInBytes() { return sizeof(Vector<N, T>); }

  Vector() { data.fill(static_cast<T>(0)); }
  Vector(T value) { data.fill(value); }

  template <typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
  Vector(Args... args) : data{static_cast<T>(args)...} {}

  T &operator[](size_t idx) { return data[idx]; }
  const T &operator[](size_t idx) const { return data[idx]; }

  const T &X() const {
    static_assert(N >= 1, "Vector has no X component");
    return data[0];
  }
  const T &Y() const {
    static_assert(N >= 2, "Vector has no Y component");
    return data[1];
  }
  const T &Z() const {
    static_assert(N >= 3, "Vector has no Z component");
    return data[2];
  }
  const T &W() const {
    static_assert(N >= 4, "Vector has no W component");
    return data[3];
  }
  T &X() {
    static_assert(N >= 1, "Vector has no X component");
    return data[0];
  }
  T &Y() {
    static_assert(N >= 2, "Vector has no Y component");
    return data[1];
  }
  T &Z() {
    static_assert(N >= 3, "Vector has no Z component");
    return data[2];
  }
  T &W() {
    static_assert(N >= 4, "Vector has no W component");
    return data[3];
  }

  constexpr T Length() const {
    T sum = static_cast<T>(0);
    for (size_t i = 0; i < N; i++)
      sum += data[i] * data[i];
    return std::sqrt(sum);
  }
  constexpr T ReciprocalLengthFast() const {
    T sum = static_cast<T>(0);
    for (size_t i = 0; i < N; i++)
      sum += data[i] * data[i];
    return MathHelper::InverseSqrtFast<T>(sum);
  }
  constexpr T LengthFast() const {
    return static_cast<T>(1.0f) / ReciprocalLengthFast();
  }
  constexpr T LengthSquared() const {
    T sum = 0;
    for (size_t i = 0; i < N; i++) {
      sum += data[i] * data[i];
    }
    return sum;
  }
  constexpr Vector Normalized() const {
    Vector v = *this;
    v.Normalize();
    return v;
  }
  void Normalize() {
    T scale = static_cast<T>(1.0f) / Length();
    for (size_t i = 0; i < N; i++)
      data[i] *= scale;
  }
  constexpr Vector Abs() const {
    Vector result = *this;
    for (size_t i = 0; i < N; i++) {
      result.data[i] = std::abs(result.data[i]);
    }
    return result;
  }
  constexpr Vector Round() const { return Round(*this); }
  constexpr Vector Round(MidpointRounding rounding) const {
    return Round(*this, rounding);
  }
  constexpr Vector Ceiling() const { return Ceiling(*this); }
  constexpr Vector Floor() const { return Floor(*this); }
  constexpr Vector Truncate() const { return Truncate(*this); }
  constexpr static Vector Add(const Vector &a, const Vector b) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = a.data[i] + b.data[i];
    return res;
  }
  constexpr static Vector Subtract(const Vector &a, const Vector b) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = a.data[i] - b.data[i];
    return res;
  }
  constexpr static Vector Multiply(const Vector &a, const Vector b) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = a.data[i] * b.data[i];
    return res;
  }
  constexpr static Vector Multiply(const Vector &a, T scale) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = a.data[i] * scale;
    return res;
  }
  constexpr static Vector Divide(const Vector &a, const Vector b) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = a.data[i] / b.data[i];
    return res;
  }
  constexpr static Vector Divide(const Vector &a, T scale) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = a.data[i] / scale;
    return res;
  }
  constexpr Vector operator+(const Vector &a) const {
    Vector res = *this;
    for (size_t i = 0; i < N; i++)
      res.data[i] += a.data[i];
    return res;
  };
  Vector operator+=(const Vector &a) {
    for (size_t i = 0; i < N; i++) {
      data[i] += a.data[i];
    }
    return *this;
  }
  constexpr Vector operator-(const Vector &a) const {
    Vector res = *this;
    for (size_t i = 0; i < N; i++)
      res.data[i] -= a.data[i];
    return res;
  }
  Vector operator-=(const Vector &a) {
    for (size_t i = 0; i < N; i++)
      data[i] -= a.data[i];
    return *this;
  }
  constexpr Vector operator*(const Vector &a) const {
    Vector res = *this;
    for (size_t i = 0; i < N; i++)
      res.data[i] *= a.data[i];
    return res;
  }
  constexpr friend Vector operator*(T scalar, const Vector &v) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = v.data[i] * scalar;
    return res;
  }
  constexpr friend Vector operator*(const Vector &v, T scalar) {
    return scalar * v;
  }

  Vector operator*=(const Vector &a) {
    for (size_t i = 0; i < N; i++)
      data[i] *= a.data[i];
    return *this;
  }
  constexpr Vector operator/(const Vector &a) const {
    Vector res = *this;
    for (size_t i = 0; i < N; i++)
      res.data[i] /= a.data[i];
    return res;
  }
  Vector operator/=(const Vector &a) {
    for (size_t i = 0; i < N; i++)
      data[i] /= a.data[i];
    return *this;
  }

  constexpr static Vector ComponentMin(const Vector &a, const Vector &b) {
    Vector<N, T> m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = a.data[i] < b.data[i] ? a.data[i] : b.data[i];
    return m;
  }
  constexpr static Vector ComponentMax(const Vector &a, const Vector &b) {
    Vector<N, T> m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = a.data[i] > b.data[i] ? a.data[i] : b.data[i];
    return m;
  }
  constexpr static Vector MagnitudeMin(const Vector &a, const Vector &b) {
    return a.LengthSquared() < b.LengthSquared() ? a : b;
  }
  constexpr static Vector MagnitudeMax(const Vector &a, const Vector &b) {
    return a.LengthSquared() > b.LengthSquared() ? a : b;
  }
  constexpr static Vector Clamp(const Vector &v, const Vector &min,
                                const Vector &max) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = v.data[i] < min.data[i]   ? min.data[i]
                    : v.data[i] > max.data[i] ? max.data[i]
                                              : v.data[i];
    return res;
  }
  constexpr static Vector Abs(const Vector &v) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = std::abs(v.data[i]);
    return res;
  }
  constexpr static Vector Round(const Vector &v) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = MathHelper::Round(v.data[i]);
    return res;
  }
  constexpr static Vector Round(const Vector &v, MidpointRounding m) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = MathHelper::Round(v.data[i], m);
    return res;
  }
  constexpr static Vector Ceiling(const Vector &v) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = std::ceil(v.data[i]);
    return res;
  }
  constexpr static Vector Floor(const Vector &v) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = std::floor(v.data[i]);
    return res;
  }
  constexpr static Vector Truncate(const Vector &v) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = std::trunc(v.data[i]);
    return res;
  }
  static T Distance(const Vector &a, const Vector &b) {
    return std::sqrt(DistanceSquared(a, b));
  }
  static T DistanceSquared(const Vector &a, const Vector &b) {
    T res = static_cast<T>(0);
    for (size_t i = 0; i < N; i++)
      res += (b.data[i] - a.data[i]) * (b.data[i] - a.data[i]);
    return res;
  }
  constexpr static Vector Normalize(const Vector &v) {
    T scale = static_cast<T>(1.0f) / v.Length();
    Vector res = v;
    for (size_t i = 0; i < N; i++)
      res.data[i] *= scale;
    return res;
  }
  constexpr static Vector NormalizeFast(const Vector &v) {
    T scale = MathHelper::InverseSqrtFast(v.LengthSquared());
    Vector res = v;
    for (size_t i = 0; i < N; i++)
      res.data[i] *= scale;
    return res;
  }
  static T Dot(const Vector &a, const Vector &b) {
    T sum = static_cast<T>(0);
    for (size_t i = 0; i < N; i++)
      sum += a.data[i] * b.data[i];
    return sum;
  }
  static Vector<N, bool> LessThan(const Vector &a, const Vector &b) {
    Vector<N, bool> m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = a.data[i] < b.data[i];
    return m;
  }
  static Vector<N, bool> LessThanOrEqual(const Vector &a, const Vector &b) {
    Vector<N, bool> m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = a.data[i] <= b.data[i];
    return m;
  }
  static Vector<N, bool> GreaterThan(const Vector &a, const Vector &b) {
    Vector<N, bool> m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = a.data[i] > b.data[i];
    return m;
  }
  static Vector<N, bool> GreaterThanOrEqual(const Vector &a, const Vector &b) {
    Vector<N, bool> m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = a.data[i] >= b.data[i];
    return m;
  }
  static Vector<N, bool> ComponentEqual(const Vector &a, const Vector &b) {
    Vector<N, bool> m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = a.data[i] == b.data[i];
    return m;
  }
  static Vector<N, bool> ComponentNotEqual(const Vector &a, const Vector &b) {
    Vector<N, bool> m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = a.data[i] != b.data[i];
    return m;
  }
  constexpr static Vector Lerp(const Vector &a, const Vector &b, T blend) {
    Vector m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = (blend * (b.data[i] - a.data[i])) + a.data[i];
    return m;
  }
  constexpr static Vector Lerp(const Vector &a, const Vector &b,
                               const Vector &blend) {
    Vector m;
    for (size_t i = 0; i < N; i++)
      m.data[i] = (blend.data[i] * (b.data[i] - a.data[i])) + a.data[i];
    return m;
  }
  constexpr static Vector Slerp(const Vector &a, const Vector &b, T t) {
    T abLength = a.Length() * b.Length();
    T cosTheta = static_cast<T>(0);
    if (abLength == static_cast<T>(0) ||
        std::abs(cosTheta = Dot(a, b) / abLength) > 0.9999f) {
      return Lerp(a, b, t);
    }
    T theta = std::acos(std::clamp(cosTheta, -1, 1));
    T sinTheta = std::sqrt(1 - (cosTheta * cosTheta));
    T bcoef = std::sin(t * theta) / sinTheta;
    T acoef = std::sin((1 - t) * theta) / sinTheta;
    return (acoef * a) + (bcoef * b);
  }
  constexpr static Vector Elerp(const Vector &a, const Vector &b, T t) {
    Vector res;
    for (size_t i = 0; i < N; i++)
      res.data[i] = std::pow(a.data[i], 1 - t) * std::pow(b.data[i], t);
    return res;
  }
  constexpr static Vector BaryCentric(const Vector &a, const Vector &b,
                                      const Vector &c, T u, T v) {
    Vector ab = Subtract(a, b);
    Vector abU = Multiply(ab, u);
    Vector uPos = Add(a, abU);
    Vector ac = Subtract(c, a);
    Vector acV = Multiply(ac, v);
    return Add(uPos, acV);
  }

  constexpr static Vector Cross(const Vector &left, const Vector &right)
    requires(N == 3)
  {
    return Vector{(left.Y() * right.Z()) - (left.Z() * right.Y()),
                  (left.Z() * right.X()) - (left.X() * right.Z()),
                  (left.X() * right.Y()) - (left.Y() * right.X())};
  }

  friend Vector<N, bool> operator<(const Vector &a, const Vector &b) {
    return LessThan(a, b);
  }
  friend Vector<N, bool> operator<=(const Vector &a, const Vector &b) {
    return LessThanOrEqual(a, b);
  }
  friend Vector<N, bool> operator>(const Vector &a, const Vector &b) {
    return GreaterThan(a, b);
  }
  friend Vector<N, bool> operator>=(const Vector &a, const Vector &b) {
    return GreaterThanOrEqual(a, b);
  }
  friend Vector<N, bool> operator==(const Vector &a, const Vector &b) {}

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

  template <size_t S>
  static constexpr Vector<S, T> GetSubVector(const Vector<N, T> &v,
                                             size_t indexes[S])
    requires(S <= N)
  {
    Vector<S, T> v_{};
    for (size_t i = 0; i < S; i++)
      v_.data[i] = v.data[indexes[i]];
    return v_;
  }
  template <size_t S>
  constexpr Vector<S, T> GetSubVector(size_t indexes[S])
    requires(S <= N)
  {
    Vector<S, T> v_{};
    for (size_t i = 0; i < S; i++)
      v_.data[i] = data[indexes[i]];
    return v_;
  }
  template <size_t... Is>
  constexpr Vector<sizeof...(Is), T> GetSubVector() const {
    static_assert(((Is < N) && ...), "Index out of bounds");
    return {data[Is]...};
  }
  template <size_t S>
  static constexpr void SetSubVector(const Vector<N, T> &orig,
                                     const Vector<S, T> &sub, size_t indexes[S])
    requires(S <= N)
  {
    for (size_t i = 0; i < S; i++)
      orig.data[indexes[i]] = sub.data[i];
  }
  template <size_t S>
  constexpr void SetSubVector(const Vector<S, T> &sub, size_t indexes[S])
    requires(S <= N)
  {
    for (size_t i = 0; i < S; i++)
      data[indexes[i]] = sub.data[i];
  }
  template <size_t... Is>
  constexpr void SetSubVector(const Vector<sizeof...(Is), T> &sub) {
    static_assert(((Is < N) && ...), "Index out of bounds");
    size_t i = 0;
    ((data[Is] = sub.data[i++]), ...);
  }
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
