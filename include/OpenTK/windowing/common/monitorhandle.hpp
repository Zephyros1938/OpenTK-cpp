#pragma once
#include <OpenTK/Ported/intptr.hpp>

namespace OpenTK {
namespace windowing {
namespace common {
struct MonitorHandle {
  Ported::IntPtr Pointer;
  MonitorHandle(Ported::IntPtr ptr) : Pointer(ptr) {}
  template <typename T> T *ToUnsafePtr() { return static_cast<T *>(Pointer); }
};
} // namespace common
} // namespace windowing

} // namespace OpenTK
