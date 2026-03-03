#pragma once

#include <span>

namespace OpenTK::Ported {
template <typename T> using ReadOnlySpan = std::span<const T>;
} // namespace OpenTK::Ported
