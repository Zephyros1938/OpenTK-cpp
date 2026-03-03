#pragma once

#include "windowhintreleasebehavior.hpp"
#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class WindowAttributeGetReleaseBehavior : uint32_t {
  ContextReleaseBehavior =
      static_cast<uint32_t>(WindowHintReleaseBehavior::ContextReleaseBehavior)
};
}
} // namespace windowing

} // namespace OpenTK
