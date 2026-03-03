#pragma once

#include "OpenTK/Windowing/Common/Input/Enums/Hat.hpp"
#include <GLFW/glfw3.h>
#include <bitset>
#include <cstring>
#include <vector>

namespace OpenTK::windowing::graphicsframework {
class JoystickState {
  std::vector<common::input::Hat> _hats;
  std::vector<float> _axes;
  std::bitset<16> _buttons;

  std::vector<common::input::Hat> _hatsPrevious;
  std::vector<float> _axesPrevious;
  std::bitset<16> _buttonsPrevious;

public:
  int Id;
  std::string Name;
  std::string GUID;
  int ButtonCount() { return _buttons.size(); }
  int AxisCount() { return _axes.size(); }
  int HatCount() { return _hats.size(); }
};
} // namespace OpenTK::windowing::graphicsframework
