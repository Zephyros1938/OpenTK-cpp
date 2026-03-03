#pragma once
#include <OpenTK/Ported/IntPtr.hpp>

namespace OpenTK::Windowing::Common {
struct MonitorHandle {
  Ported::IntPtr Pointer;
  MonitorHandle(Ported::IntPtr ptr) : Pointer(ptr) {}
  template <typename T> T *ToUnsafePtr() { return static_cast<T *>(Pointer); }
};
} // namespace OpenTK::windowing::common
