#pragma once
#include "../../../core/intptr.hpp"

namespace OpenTK {
namespace windowing {
namespace common {
struct MonitorHandle {
  core::IntPtr Pointer;
  MonitorHandle(core::IntPtr ptr) : Pointer(ptr) {}
  template <typename T> T *ToUnsafePtr() { return static_cast<T *>(Pointer); }
};
} // namespace common
} // namespace windowing

} // namespace OpenTK
