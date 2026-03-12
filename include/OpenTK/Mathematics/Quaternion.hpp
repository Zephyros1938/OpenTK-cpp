#pragma once

#include "OpenTK/Mathematics/MathHelper.hpp"
#include "OpenTK/Mathematics/Matrix.hpp"
#include "OpenTK/Mathematics/Vector.hpp"
#include <cmath>
namespace OpenTK::Mathematics {
template <typename T = float> struct Quaternion {
  Vector<3, T> Xyz;
  T W;

  Quaternion(Vector<3, T> v, T w) : Xyz(v), W(w) {}
  Quaternion(T x, T y, T z, T w) : Xyz(x, y, z), W(w) {}
  Quaternion(T rotX, T rotY, T rotZ) {
    rotX *= static_cast<T>(0.5f);
    rotY *= static_cast<T>(0.5f);
    rotZ *= static_cast<T>(0.5f);

    T c1 = static_cast<T>(std::cos(rotX));
    T c2 = static_cast<T>(std::cos(rotY));
    T c3 = static_cast<T>(std::cos(rotZ));
    T s1 = static_cast<T>(std::sin(rotX));
    T s2 = static_cast<T>(std::sin(rotY));
    T s3 = static_cast<T>(std::sin(rotZ));

    W = (c1 * c2 * c3) - (s1 * s2 * s3);
    Xyz.data[0] = (s1 * c2 * c3) + (c1 * s2 * s3);
    Xyz.data[1] = (c1 * s2 * c3) - (s1 * c2 * s3);
    Xyz.data[2] = (c1 * c2 * s3) + (s1 * s2 * c3);
  }
  Quaternion(Vector<3, T> eulerAngles)
      : Quaternion(eulerAngles.X(), eulerAngles.Y(), eulerAngles.Z()) {}

  constexpr void ToAxisAngle(Vector<3, T> *axis, Vector<3, T> *angle) {
    auto result = ToAxisAngle();
    axis = result.Xyz;
    angle = result.W;
  }
  constexpr Vector<4, T> ToAxisAngle() {
    auto q = *this;
    if (std::abs(q.W) > 1.0f)
      q.Normalize();
    auto result =
        Vector<4, T>{W = static_cast<T>(2.0f) * static_cast<T>(std::acos(q.W))};
    auto den = std::sqrt(static_cast<T>(1.0f) - (q.W * q.W));
    if (den > static_cast<T>(0.0001f))
      result.template SetSubVector<0, 1, 2>(q.Xyz / den);
    else
      result.template SetSubVector<0, 1, 2>(Vector<3, T>{1, 0, 0});
    return result;
  }
  constexpr void ToEulerAngles(Vector<3, T> *angles) const {
    angles = ToEulerAngles();
  }
  constexpr Vector<3, T> ToEulerAngles() const {
    auto q = *this;

    Vector<3, T> eulerAngles;

    const T SINGULARITY_THRESHOLD = static_cast<T>(0.4999995f);

    auto sqw = q.W * q.W;
    auto sqx = q.Xyz.X() * q.Xyz.X();
    auto sqy = q.Xyz.Y() * q.Xyz.Y();
    auto sqz = q.Xyz.Z() * q.Xyz.Z();
    auto unit = sqx + sqy + sqz + sqw;
    auto singularityTest = (q.Xyz.X() * q.Xyz.Z()) + (q.W * q.Xyz.Y());

    if (singularityTest > SINGULARITY_THRESHOLD * unit) {
      eulerAngles.data[2] = static_cast<T>(2 * std::atan2(q.Xyz.X(), q.W));
      eulerAngles.data[1] = static_cast<T>(MathHelper::PiOver2);
      eulerAngles.data[0] = static_cast<T>(0);
    } else if (singularityTest < -SINGULARITY_THRESHOLD * unit) {
      eulerAngles.data[2] = static_cast<T>(-2 * std::atan2(q.Xyz.X(), q.W));
      eulerAngles.data[1] = static_cast<T>(-MathHelper::PiOver2);
      eulerAngles.data[0] = static_cast<T>(0);
    } else {
      eulerAngles.data[2] = static_cast<T>(
          std::atan2(2 * ((q.W * q.Xyz.Z()) - (q.Xyz.X() * q.Xyz.Y())),
                     sqw + sqx - sqy - sqz));
      eulerAngles.data[1] =
          static_cast<T>(std::asin(2 * singularityTest / unit));
      eulerAngles.data[20] = static_cast<T>(
          std::atan2(2 * ((q.W * q.Xyz.X()) - (q.Xyz.Y() * q.Xyz.Z())),
                     sqw - sqx - sqy + sqz));
    }
    return eulerAngles;
  }
  constexpr T Length() const {
    return static_cast<T>(std::sqrt((W * W) + Xyz.LengthSquared()));
  }
  constexpr T LengthSquared() const { return (W * W) + Xyz.LengthSquared(); }
  constexpr Quaternion Normalized() const {
    auto q = *this;
    q.Normalize();
    return q;
  }
  constexpr void Invert() { Invert(this); }
  constexpr void Normalize() {
    auto scale = static_cast<T>(1.0f) / Length();
    Xyz *= scale;
    W *= scale;
  }
  constexpr void Conjugate() { Xyz = -Xyz; }
  constexpr static Quaternion Identity() { return Quaternion(0, 0, 0, 1); }
  constexpr static Quaternion Add(const Quaternion &left,
                                  const Quaternion &right) {
    return Quaternion(left.Xyz + right.Xyz, left.W + right.W);
  }
  constexpr static Quaternion Sub(const Quaternion &left,
                                  const Quaternion &right) {
    return Quaternion(left.Xyz - right.Xyz, left.W - right.W);
  }
  constexpr static Quaternion Multiply(const Quaternion &left,
                                       const Quaternion &right) {
    return Quaternion((right.W * left.Xyz) + (left.W * right.Xyz) +
                          Vector<3, T>::Cross(left.Xyz, right.Xyz),
                      (left.W * right.W) -
                          Vector<3, T>::Dot(left.Xyz, right.Xyz));
  }
  constexpr static Quaternion Multiply(const Quaternion &quaternion, T scale) {
    return Quaternion(quaternion.Xyz.X() * scale, quaternion.Xyz.Y() * scale,
                      quaternion.Xyz.Z() * scale, quaternion.W * scale);
  }
  constexpr static Quaternion Conjugate(const Quaternion &q) {
    return Quaternion(-q.Xyz, -q.W);
  }
  constexpr static Quaternion Invert(const Quaternion &q) {
    auto lengthSq = q.LengthSquared();
    if (lengthSq != static_cast<T>(0.0)) {
      auto i = static_cast<T>(1.0f) / lengthSq;
      return Quaternion(q.Xyz * -i, q.W * i);
    }
    return q;
  }
  constexpr static Quaternion Normalize(const Quaternion &q) {
    auto scale = static_cast<T>(1.0f) / q.Length();
    return Quaternion(q.Xyz * scale, q.W * scale);
  }
  constexpr static Quaternion FromAxisAngle(Vector<3, T> axis, T angle) {
    if (axis.LengthSquared() == static_cast<T>(0.0f))
      return Identity();
    auto result = Identity();
    angle *= static_cast<T>(0.5f);
    axis.Normalize();
    return Quaternion(axis * std::sin(angle), std::cos(angle)).Normalized();
  }
  constexpr static Quaternion FromEulerAngles(T pitch, T yaw, T roll) {
    return Quaternion(pitch, yaw, roll);
  }
  constexpr static Quaternion FromEulerAngles(Vector<3, T> eulerAngles) {
    return Quaternion(eulerAngles);
  }
  constexpr static Quaternion FromMatrix(Matrix<3, 3, T> matrix) {
    auto trace = matrix.Trace();
    if (trace > static_cast<T>(0)) {
      auto s = std::sqrt(trace + static_cast<T>(1)) * static_cast<T>(2);
      auto invS = static_cast<T>(1.0f) / s;
      return Quaternion((matrix[2][1] - matrix[1][2]) * invS,
                        (matrix[0][2] - matrix[2][0]) * invS,
                        (matrix[1][0] - matrix[0][1]) * invS,
                        s * static_cast<T>(0.25f));
    }
    T m00 = matrix[0][0], m11 = matrix[1][1], m22 = matrix[2][2];
    if (m00 > m11 && m00 > m22) {
      auto s =
          std::sqrt(static_cast<T>(1) + m00 - m11 - m22) * static_cast<T>(2);
      auto invS = static_cast<T>(1) / s;
      return Quaternion(s * static_cast<T>(0.25f),
                        (matrix[0][1] + matrix[1][0]) * invS,
                        (matrix[0][2] + matrix[2][0]) * invS,
                        (matrix[2][1] - matrix[1][2]) * invS);
    } else if (m11 > m22) {
      auto s =
          std::sqrt(static_cast<T>(1) + m11 - m00 - m22) * static_cast<T>(2);
      auto invS = static_cast<T>(1) / s;
      return Quaternion((matrix[0][1] + matrix[1][0]) * invS,
                        s * static_cast<T>(0.25f),
                        (matrix[1][2] + matrix[2][1]) * invS,
                        (matrix[0][2] - matrix[2][0]) * invS);
    } else {
      auto s =
          std::sqrt(static_cast<T>(1) + m22 - m00 - m11) * static_cast<T>(2);
      auto invS = static_cast<T>(1) / s;
      return Quaternion((matrix[0][2] + matrix[2][0]) * invS,
                        (matrix[1][2] + matrix[2][1]) * invS,
                        s * static_cast<T>(0.25f),
                        (matrix[1][0] - matrix[0][1]) * invS);
    }
  }
  constexpr static Quaternion Slerp(const Quaternion &q1, const Quaternion &q2,
                                    T blend) {
    if (q1.LengthSquared() == static_cast<T>(0.0f)) {
      if (q2.LengthSquared() == static_cast<T>(0.0f))
        return Identity();
      return q2;
    }
    if (q2.LengthSquared() == static_cast<T>(0.0f))
      return q1;
    auto cosHalfAngle = (q1.W * q2.W) + Vector<3, T>::Dot(q1.Xyz, q2.Xyz);
    if (cosHalfAngle >= static_cast<T>(1.0f) ||
        cosHalfAngle <= static_cast<T>(-1.0f))
      return q1;
    if (cosHalfAngle < static_cast<T>(0.0f)) {
      q2.Xyz = -q2.Xyz;
      q2.W = -q2.W;
      cosHalfAngle = -cosHalfAngle;
    }
    T blendA = 0;
    T blendB = 0;
    if (cosHalfAngle < static_cast<T>(0.99f)) {
      auto halfAngle = std::acos(cosHalfAngle);
      auto sinHalfAngle = std::sin(halfAngle);
      auto oneOverSinHalfAngle = static_cast<T>(1.0f) / sinHalfAngle;
      blendA = std::sin(halfAngle * (static_cast<T>(1.0f) - blend)) *
               oneOverSinHalfAngle;
      blendB = std::sin(halfAngle * blend) * oneOverSinHalfAngle;
    } else {
      blendA = static_cast<T>(1.0f) - blend;
      blendB = blend;
    }
    auto result = Quaternion((blendA * q1.Xyz) + (blendB * q2.Xyz),
                             (blendA * q1.W) + (blendB * q2.W));
    if (result.LengthSquared() > static_cast<T>(0.0f))
      return Normalize(result);
    return Identity();
  }
  friend Quaternion operator+(const Quaternion &left, const Quaternion &right) {
    return Quaternion(left.Xyz + right.Xyz, left.W + right.W);
  }
  friend Quaternion operator-(const Quaternion &left, const Quaternion &right) {
    return Quaternion(left.Xyz - right.Xyz, left.W - right.W);
  }
  friend Quaternion operator*(const Quaternion &left, const Quaternion &right) {
    return Multiply(left, right);
  }
  friend Quaternion operator*(const Quaternion &left, T scale) {
    return Multiply(left, scale);
  }
  friend bool operator==(const Quaternion &left, const Quaternion &right) {
    return left.Xyz == right.Xyz && left.W == right.W;
  }
  friend bool operator/=(const Quaternion &left, const Quaternion &right) {
    return !(left == right);
  }

  friend std::ostream &operator<<(std::ostream &os, const Quaternion<T> &v) {
    os << "V: " << v.Xyz << " W: " << v.W;
    return os;
  }
};
} // namespace OpenTK::Mathematics
