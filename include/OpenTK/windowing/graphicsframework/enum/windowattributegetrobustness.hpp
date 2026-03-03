#pragma once

#include "windowhintrobustness.hpp"
#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class WindowAttributeGetRobustness : uint32_t {
  ContextRobustness =
      static_cast<uint32_t>(WindowHintRobustness::ContextRobustness)
};
}
