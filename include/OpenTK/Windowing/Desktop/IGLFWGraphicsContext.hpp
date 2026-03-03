#pragma once

#include <OpenTK/Ported/IntPtr.hpp>
#include <OpenTK/Windowing/Common/Interfaces/IGraphicsContext.hpp>

namespace OpenTK::Windowing::Desktop {
class IGLFWGraphicsContext {
public:
  virtual ~IGLFWGraphicsContext() = 0;
  Ported::IntPtr WindowPtr;
};
} // namespace OpenTK::Windowing::Desktop
