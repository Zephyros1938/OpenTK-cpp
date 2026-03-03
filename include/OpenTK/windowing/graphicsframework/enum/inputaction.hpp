#pragma once

#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class InputAction : uint32_t { Release = 0, Press, Repeat };
}
