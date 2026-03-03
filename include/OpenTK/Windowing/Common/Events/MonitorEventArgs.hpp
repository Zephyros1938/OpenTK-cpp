#pragma once

#include <OpenTK/Windowing/Common/MonitorHandle.hpp>
namespace OpenTK::Windowing::Common {
struct MonitorEventArgs {
  MonitorHandle Monitor;
  bool IsConnected;

  MonitorEventArgs(MonitorHandle monitor, bool isConnected)
      : Monitor(monitor), IsConnected(isConnected) {}
};
} // namespace OpenTK::windowing::common
