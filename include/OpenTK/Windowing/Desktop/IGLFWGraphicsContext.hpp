#pragma once

#include <OpenTK/Ported/IntPtr.hpp>
#include <OpenTK/Windowing/Common/Interfaces/IGraphicsContext.hpp>

namespace OpenTK::Windowing::Desktop {
class IGLFWGraphicsContext : Windowing::Common::IGraphicsContext {
public:
  explicit IGLFWGraphicsContext(Ported::IntPtr WindowPtr)
      : WindowPtr(WindowPtr) {}
  virtual ~IGLFWGraphicsContext() = 0;
  Ported::IntPtr WindowPtr;
};
} // namespace OpenTK::Windowing::Desktop
