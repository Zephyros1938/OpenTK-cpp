#pragma once

#include "OpenTK/Mathematics/MathHelper.hpp"
#include "OpenTK/Mathematics/Vector.hpp"
#include <cmath>
namespace OpenTK::Mathematics {
template <typename T = float> struct Quaternion {
  Vector<3, T> Xyz;
  T W;
  Quaternion(Vector<3, T> v, T w) : Xyz(v), W(w) {}
  Quaternion(T x, T y, T z, T w) : Xyz(x, y, z), W(w) {}
  Quaternion(T rotationX, T rotationY, T rotationZ) {
    rotationX *= static_cast<T>(0.5);
    rotationY *= static_cast<T>(0.5);
    rotationZ *= static_cast<T>(0.5);
    T c1 = std::cos(static_cast<T>(rotationX));
    T c2 = std::cos(static_cast<T>(rotationY));
    T c3 = std::cos(static_cast<T>(rotationZ));
    T s1 = std::sin(static_cast<T>(rotationX));
    T s2 = std::sin(static_cast<T>(rotationY));
    T s3 = std::sin(static_cast<T>(rotationZ));
    W = (c1 * c2 * c3) - (s1 * s2 * s3);
    Xyz.data[0] = (s1 * c2 * c3) + (c1 * s2 * s3);
    Xyz.data[1] = (c1 * s2 * c3) - (s1 * c2 * s3);
    Xyz.data[2] = (c1 * c2 * s3) + (s1 * s2 * c3);
  }
  Quaternion(Vector<3, T> eulerAngles) {
    this = Quaternion(eulerAngles.X(), eulerAngles.Y(), eulerAngles.Z());
  }
  constexpr void ToAxisAngle(Vector<3, T> *axis, T *angle) const {
    auto res = ToAxisAngle();
    axis = res.GetSubVector(0, 1, 2);
    angle = res.GetSubVector(3);
  }
  constexpr Vector<4, T> ToAxisAngle() const {
    auto q = *this;
    if (std::abs(q.W) > static_cast<T>(1.0f))
      q.Normalize();
    W = static_cast<T>(2.0f) * std::acos(q.W);
    auto res = Vector<4, T>{W};
    auto den = std::sqrt(static_cast<T>(1.0f) - (q.W * q.W));
    if (den > static_cast<T>(0.0001f))
      res.SetSubVector(q.Xyz / den, 0, 1, 2);
    else
      res.SetSubVector(Vector<3, T>(1, 0, 0), 0, 1, 2);
    return res;
  }
  constexpr void ToEulerAngles(Vector<3, T> *angles) const {
    angles = ToEulerAngles();
  }
  constexpr Vector<3, T> ToEulerAngles() const {
    auto q = *this;
    Vector<3, T> eulerAngles;
    const T SINGULARITY_THRESHOLD = static_cast<T>(0.4999995f);
    auto sqw = q.W * q.W;
    auto sqx = q.Xyz[0] * q.Xyz[0];
    auto sqy = q.Xyz[1] * q.Xyz[1];
    auto sqz = q.Xyz[2] * q.Xyz[2];
    auto unit = sqx + sqy + sqz + sqw;
    auto singularityTest = (q.Xyz[0] * q.Xyz[2]) + (q.W * q.Xyz[1]);
    // INFO: std::atan2 is safer
    if (singularityTest > SINGULARITY_THRESHOLD * unit) {
      eulerAngles.data[2] = static_cast<T>(2) * std::atan2(q.Xyz[0], q.W);
      eulerAngles.data[1] = static_cast<T>(MathHelper::PiOver2);
      eulerAngles.data[0] = 0;
    } else if (singularityTest < -SINGULARITY_THRESHOLD * unit) {
      eulerAngles.data[2] = static_cast<T>(-2) * std::atan2(q.Xyz[0], q.W);
      eulerAngles.data[1] = static_cast<T>(-MathHelper::PiOver2);
      eulerAngles.data[0] = 0;
    } else {
      eulerAngles.data[2] =
          std::atan2(2 * ((q.W * q.Xyz[2]) - (q.Xyz[0] * q.Xyz[1])),
                     sqw + sqx - sqy - sqz);
      eulerAngles.data[1] = std::asin(2 * singularityTest / unit);
      eulerAngles.data[0] =
          std::atan2(2 * ((q.W * q.Xyz[0]) - (q.Xyz[1] * q.Xyz[2])),
                     sqw - sqx - sqy + sqz);
    }
    return eulerAngles;
  }
  constexpr T Length() const {
    return std::sqrt((W * W) + Xyz.LengthSquared());
  }
  constexpr T LengthSquared() const { return (W * W) + Xyz.LengthSquared(); }
  constexpr Quaternion Normalized() const {
    auto q = *this;
    q.Normalize();
    return q;
  }
  constexpr void Normalize() const {
    auto scale = static_cast<T>(1.0f) / Length();
    Xyz *= scale;
    W *= scale;
  }
};
} // namespace OpenTK::Mathematics
