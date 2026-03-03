#pragma once

#include <GLFW/glfw3.h>
#include <cstring>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
struct GamepadState {
  unsigned char Buttons[15];
  float Axes[6];

  operator GLFWgamepadstate *() {
    GLFWgamepadstate *gs = new GLFWgamepadstate();

    memcpy(gs->buttons, Buttons, sizeof(Buttons));
    memcpy(gs->axes, Axes, sizeof(Axes));

    return gs;
  }
};
} // namespace graphicsframework
} // namespace windowing

} // namespace OpenTK
