#pragma once
#include "OpenTK/Mathematics/Enums/MidpointRounding.hpp"
#include "OpenTK/Mathematics/Types.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <stdfloat>
#include <utility>

namespace OpenTK::Mathematics {

class MathHelper {
public:
  static constexpr float Pi = 3.1415924;
  static constexpr float PiOver2 = Pi / 2;
  static constexpr float PiOver3 = Pi / 3;
  static constexpr float PiOver4 = Pi / 4;
  static constexpr float PiOver6 = Pi / 6;
  static constexpr float TwoPi = Pi * 2;
  static constexpr float ThreePiOver2 = 3 * Pi / 2;
  static constexpr float E = 2.7182817;
  static constexpr float Log10E = 0.4342945;
  static constexpr float Log2E = 1.442695;
  static constexpr float RadToDeg = 180 / Pi;
  static constexpr float DegToRad = Pi / 180;
  static constexpr double RadToDegd = 180 / 3.1415926535897931;
  static constexpr double DegToRadd = 3.1415926535897931 / 180;
  constexpr static auto Abs(Scalar auto v) { return v < 0 ? -v : v; }
  constexpr static auto Sin(Real auto v) { return std::sin(v); }
  constexpr static auto Sinh(Real auto v) { return std::sinh(v); }
  constexpr static auto Asin(Real auto v) { return std::asin(v); }
  constexpr static auto Cos(Real auto v) { return std::cos(v); }
  constexpr static auto Cosh(Real auto v) { return std::cosh(v); }
  constexpr static auto Acos(Real auto v) { return std::acos(v); }
  constexpr static auto Tan(Real auto v) { return std::tan(v); }
  constexpr static auto Tanh(Real auto v) { return std::tanh(v); }
  constexpr static auto Atan(Real auto v) { return std::atan(v); }
  constexpr static auto Atan2(Real auto v) { return std::atan2(v); }
  constexpr static auto BigMul(Integral auto a, Integral auto b) {
    return (int128)a * b;
  }
  constexpr static auto Sqrt(Real auto n) { return std::sqrt(n); }
  constexpr static auto Pow(Scalar auto x, Scalar auto y) {
    return std::pow(x, y);
  }
  constexpr static auto Ceiling(Scalar auto n) { return std::ceil(n); }
  constexpr static auto Floor(Scalar auto n) { return std::floor(n); }
  constexpr static auto DivRem(Integral auto x, Integral auto y) {
    return std::div(x, y);
  }
  constexpr static auto Log(Integral auto n) { return std::log(n); }
  constexpr static auto Log(Integral auto n, Integral auto newBase) {
    return std::log(n, newBase);
  }
  constexpr static auto Log10(Integral auto n) { return std::log10(n); }
  constexpr static auto Log2(Integral auto n) { return std::log2(n); }
  constexpr static auto Exp(Integral auto n) { return std::exp(n); }
  constexpr static auto IEEERemainder(Real auto a, Real auto b) {
    return std::remainder(a, b);
  }
  constexpr static auto Max(Scalar auto a, Scalar auto b) {
    return std::max(a, b);
  }
  constexpr static auto Min(Scalar auto a, Scalar auto b) {
    return std::min(a, b);
  }
  constexpr static auto Round(Scalar auto d) { return std::round(d); }
  constexpr static auto Round(Scalar auto d, int digits) {
    Scalar auto multiplier = Pow(10, digits);
    return std::round(d * multiplier) / multiplier;
  }
  constexpr static auto Round(Scalar auto d, int digits,
                              MidpointRounding mode) {
    Scalar auto multiplier = Pow(10, digits);
    Scalar auto shifted = d * multiplier;
    if (mode == MidpointRounding::AwayFromZero) {
      return std::round(shifted) / multiplier;
    }
    return std::nearbyint(shifted) / multiplier;
  }
  constexpr static auto Truncate(Scalar auto n) { return std::trunc(n); }
  constexpr static auto Sign(Scalar auto n) { return (n > 0) - (n < 0); }
  constexpr static auto NextPowerOfTwo(Scalar auto n) {
    if (n < 0) {
      throw std::runtime_error(
          "OpenTK::Mathematics::NextPowerOfTwo > Must be positive");
    }
    return std::pow(2, std::ceil(std::log(n, 2)));
  }
  constexpr static auto Factorial(Scalar auto n) {
    Scalar auto res = (1);
    while (1) {
      if (n < 1)
        break;
      res *= n;
    }
    return res;
  }
  constexpr static auto BinomialCoefficient(Scalar auto n, Scalar auto k) {
    return Factorial(n) / (Factorial(k) * Factorial(n - k));
  }
  constexpr static auto InverseSqrtFast(Real auto x) {
    using IntType = std::conditional_t<sizeof(x) == 8, uint64_t, uint32_t>;
    auto xhalf = static_cast<decltype(x)>(0.5) * x;
    auto i = std::bit_cast<IntType>(x);
    if constexpr (sizeof(x) == 4) {
      i = 0x5f375a86 - (i >> 1);
    } else {
      i = 0x5fe6eb50c7b537a9 - (i >> 1);
    }
    x = std::bit_cast<decltype(x)>(i);
    x = x * (static_cast<decltype(x)>(1.5) - (xhalf * x * x));

    return x;
  }
  constexpr static auto DegreesToRadians(Real auto degrees) {
    return degrees * DegToRad;
  }
  constexpr static auto RadiansToDegrees(Real auto radians) {
    return radians * RadToDeg;
  }
  // INFO: We dont even need this, this is a leftover from the original
  // implementation
  // Just use std::swap(a,b)
  template <typename T> constexpr void swap(T a, T b) { std::swap(a, b); }
  constexpr static auto Clamp(Scalar auto n, Scalar auto min, Scalar auto max) {
    return std::max(std::min(n, max), min);
  }
  constexpr static auto MapRange(Scalar auto value, Scalar auto valueMin,
                                 Scalar auto valueMax, Scalar auto resultMin,
                                 Scalar auto resultMax) {
    Scalar auto inRange = valueMax - valueMin;
    Scalar auto resultRange = resultMax - resultMin;
    return resultMax + (resultRange * ((value - valueMin) / inRange));
  }
  /*
   * I'm not adding the approximate equal functions unless i want to, they are a
   * little annoying to implement without writing 2 billion of the same
   * function. Someone should add them if they have the time to.
   * */
  constexpr static auto Lerp(Real auto start, Real auto end, Real auto t) {
    return start + (t * (end - start));
  }
  constexpr static auto Elerp(Real auto start, Real auto end, Real auto t) {
    return start + std::pow(end / start, t);
  }
  constexpr static auto NormalizeAngle(Real auto angle) {
    angle = ClampAngle(angle);
    if (angle > 180) {
      angle -= 360;
    }
    return angle;
  }
  constexpr static auto NormalizeRadians(Real auto angle) {
    angle = ClampRadians(angle);
    if (angle > Pi) {
      angle -= TwoPi;
    }
    return angle;
  }
  constexpr static auto ClampAngle(Real auto angle) {
    angle %= 360;
    if (angle < 0) {
      angle += 360;
    }
    return angle;
  }
  constexpr static auto ClampRadians(Real auto angle) {
    angle %= TwoPi;
    if (angle < 0)
      angle += TwoPi;
    return angle;
  }
};
} // namespace OpenTK::Mathematics
