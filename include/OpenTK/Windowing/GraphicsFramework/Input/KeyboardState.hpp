#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/Keys.hpp>
#include <bitset>
#include <cstring>

namespace OpenTK::windowing::graphicsframework {
class KeyboardState {
  std::bitset<(int)Keys::LastKey + 1> _keys;
  std::bitset<(int)Keys::LastKey + 1> _keysPrevious;
  KeyboardState(KeyboardState &source) {
    _keys = source._keys;
    _keysPrevious = source._keysPrevious;
  }

  // friend KeyboardState() {}
  bool operator[](Keys key) { return IsKeyDown(key); };
  void SetKeyState(Keys key, bool down) { _keys[(int)key] = down; }
  void NewFrame() {
    memset(&_keysPrevious, 0, _keysPrevious.size());
    _keysPrevious |= _keys;
  }

public:
  KeyboardState() {}
  bool IsAnyKeyDown() {
    for (size_t i = 0; i < _keys.size(); ++i) {
      if (_keys[i]) {
        return true;
      }
    }
    return false;
  }
  bool IsKeyDown(Keys key) const { return _keys[(int)key]; }
  bool WasKeyDown(Keys key) const { return _keysPrevious[(int)key]; }
  bool IsKeyPressed(Keys key) const {
    return _keys[(int)key] && !_keysPrevious[(int)key];
  }
  bool IsKeyReleased(Keys key) const {
    return !_keys[(int)key] && _keysPrevious[(int)key];
  }
  KeyboardState GetSnapshot() { return *new KeyboardState(*this); }
};
} // namespace OpenTK::windowing::graphicsframework
