#pragma once

#include "OpenTK/Windowing/Common/Input/Enums/Hat.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Enums/JoystickHats.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFW.hpp"
#include <GLFW/glfw3.h>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

namespace OpenTK::Windowing::GraphicsFramework {
class JoystickState {
  std::vector<Common::Input::Hat> _hats;
  std::vector<float> _axes;
  std::vector<bool> _buttons;

  std::vector<Common::Input::Hat> _hatsPrevious;
  std::vector<float> _axesPrevious;
  std::vector<bool> _buttonsPrevious;

  JoystickState(int hatCount, int axesCount, int buttonCount, int id,
                std::string name, std::string guid) {
    _hats.resize(hatCount);
    _axes.resize(axesCount);
    _buttons.resize(buttonCount);

    _hatsPrevious.resize(hatCount);
    _axesPrevious.resize(axesCount);
    _buttonsPrevious.resize(buttonCount);

    Id = id;
    Name = name;
    GUID = guid;
  }

  JoystickState(JoystickState &source) {
    _hats = source._hats;
    _axes = source._axes;

    for (size_t i = 0; i < _buttons.size(); ++i) {
      _buttons[i] = _buttons[i] || source._buttons[i];
    }

    _hatsPrevious = source._hatsPrevious;
    _axesPrevious = source._axesPrevious;

    for (size_t i = 0; i < _buttonsPrevious.size(); ++i) {
      _buttonsPrevious[i] = _buttonsPrevious[i] || source._buttonsPrevious[i];
    }
  }

  void SetButtonDown(int index, bool value) { _buttons[index] = value; }
  void SetAxes(ReadOnlySpan<float> axes) {
    if (axes.size() > _axes.size()) {
      _axes.resize(_axes.size());
    }
    for (int i = 0; i < _axes.size(); i++) {
      _axes[i] = axes[i];
    }
  }
  void NewFrame() {
    UpdateHats();
    UpdateAxes();
    UpdateButtons();
  }
  void UpdateButtons() {
    // auto __buttons = _buttons;
    // auto __buttonsPrevious = _buttonsPrevious;
    //_buttons = __buttonsPrevious;
    //_buttonsPrevious = __buttons;
    std::swap(_buttons, _buttonsPrevious);

    ReadOnlySpan<JoystickInputAction> buttons = GLFW::GetJoystickButtons(Id);
    for (int i = 0; i < buttons.size(); i++) {
      SetButtonDown(i, buttons[i] == JoystickInputAction::Press);
    }
  }
  void UpdateAxes() {
    // auto __axes = _axes;
    // auto __axesPrevious = _axesPrevious;
    //_axes = __axesPrevious;
    //_axesPrevious = __axes;
    std::swap(_axes, _axesPrevious);
    ReadOnlySpan<float> axes = GLFW::GetJoystickAxes(Id);
    SetAxes(axes);
  }
  void UpdateHats() {
    // auto __hats = _hats;
    // auto __hatsPrevious = _hatsPrevious;
    //_hats = __hats;
    //_hatsPrevious = __hatsPrevious;
    std::swap(_hats, _hatsPrevious);
    ReadOnlySpan<JoystickHats> hats = GLFW::GetJoystickHats(Id);
    for (int j = 0; j < hats.size(); j++) {
      SetHat(j, (Common::Input::Hat)hats[j]);
    }
  }

public:
  int Id;
  std::string Name;
  std::string GUID;
  int ButtonCount() { return _buttons.size(); }
  int AxisCount() { return _axes.size(); }
  int HatCount() { return _hats.size(); }
  Common::Input::Hat GetHat(int index) { return _hats[index]; }
  Common::Input::Hat GetHatPrevious(int index) { return _hatsPrevious[index]; }
  void SetHat(int index, Common::Input::Hat value) { _hats[index] = value; }
  bool IsButtonDown(int index) { return _buttons[index]; }
  bool WasButtonDown(int index) { return _buttonsPrevious[index]; }
  bool IsButtonPressed(int index) {
    return IsButtonDown(index) && !WasButtonDown(index);
  }
  bool IsButtonReleased(int index) {
    return !IsButtonDown(index) && WasButtonDown(index);
  }
  float GetAxis(int index) { return _axes[index]; }
  float GetAxisPrevious(int index) { return _axesPrevious[index]; }
  JoystickState GetSnapshot() { return JoystickState(*this); }
};
} // namespace OpenTK::Windowing::GraphicsFramework
