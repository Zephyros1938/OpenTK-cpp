#pragma once

#include <concepts>

namespace OpenTK::Mathematics {
#ifdef __SIZEOF_FLOAT128__
using float128 = __float128;
#else
using float128 = long double;
#endif
#ifdef __SIZEOF_INT128__
using int128 = __int128;
#else
using int128 = long long int;
#endif

template <typename T>
concept Real = std::floating_point<T> || std::same_as<T, float128>;
template <typename T>
concept Integral = std::signed_integral<T> /*)|| std::same_as<T, int128>*/;
template <typename T>
concept Scalar = Integral<T> || Real<T>;
} // namespace OpenTK::Mathematics
