#pragma once

#include <OpenTK/windowing/common/monitorhandle.hpp>

namespace OpenTK::windowing::common {
struct MonitorEventArgs {
  MonitorHandle Monitor;
  bool IsConnected;

  MonitorEventArgs(MonitorHandle monitor, bool isConnected)
      : Monitor(monitor), IsConnected(isConnected) {}
};
} // namespace OpenTK::windowing::common
