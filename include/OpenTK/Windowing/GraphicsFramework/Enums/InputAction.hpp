#pragma once

#include <cstdint>

namespace OpenTK::Windowing::GraphicsFramework {
enum class InputAction : uint32_t { Release = 0, Press, Repeat };
}
