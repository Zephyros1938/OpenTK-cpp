#pragma once

#include "windowhintopenglprofile.hpp"
#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class WindowAttributeGetOpenGlProfile : uint32_t {
  OpenGlProfile = static_cast<uint32_t>(WindowHintOpenGlProfile::OpenGlProfile)
};
}
