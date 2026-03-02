#pragma once

#include "../monitorhandle.hpp"

namespace windowing {
namespace common {
struct MonitorEventArgs {
  MonitorHandle Monitor;
  bool IsConnected;

  MonitorEventArgs(MonitorHandle monitor, bool isConnected)
      : Monitor(monitor), IsConnected(isConnected) {}
};
} // namespace common
} // namespace windowing
