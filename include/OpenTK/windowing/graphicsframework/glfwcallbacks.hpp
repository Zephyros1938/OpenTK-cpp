#pragma once

#include "enum/connectedstate.hpp"
#include "enum/errorcode.hpp"
#include "enum/inputaction.hpp"
#include "enum/keymodifiers.hpp"
#include "enum/keys.hpp"
#include "enum/mousebutton.hpp"
#include "monitor.hpp"
#include "window.hpp"
#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
namespace GLFWCallbacks {
typedef void (*CharCallback)(Window *, uint32_t);
typedef void (*CharModsCallback)(Window *, uint32_t, KeyModifiers);
typedef void (*CursorEnterCallback)(Window *, int);
typedef void (*CursorPosCallback)(Window *, double, double);
typedef void (*DropCallback)(Window *, int, char **);
typedef void (*JoystickCallback)(int, ConnectedState);
typedef void (*KeyCallback)(Window *, Keys, int, InputAction, KeyModifiers);
typedef void (*MouseButtonCallback)(Window *, MouseButton, InputAction,
                                    KeyModifiers);
typedef void (*ScrollCallback)(Window *, double, double);
typedef void (*MonitorCallback)(Monitor *, ConnectedState);
typedef void (*WindowCloseCallback)(Window *);
typedef void (*WindowFocusCallback)(Window *, int);
typedef void (*WindowIconifyCallback)(Window *, int);
typedef void (*WindowMaximizeCallback)(Window *, int);
typedef void (*FramebufferSizeCallback)(Window *, int, int);
typedef void (*WindowContentScaleCallback)(Window *, float, float);
typedef void (*WindowPosCallback)(Window *, int, int);
typedef void (*WindowSizeCallback)(Window *, int, int);
typedef void (*ErrorCallback)(ErrorCode, const char *);
typedef void (*WindowRefreshCallback)(Window *);
}; // namespace GLFWCallbacks
typedef void (*GLFWallocatefun)(size_t, void *);
typedef void (*GLFWreallocatefun)(void *, size_t, void *);
typedef void (*GLFWdeallocatefun)(void *, void *);
struct GLFWallocator {
public:
  GLFWallocatefun Allocate;
  GLFWreallocatefun Reallocate;
  GLFWdeallocatefun Deallocate;
  void *user;
};
} // namespace graphicsframework
} // namespace windowing

} // namespace OpenTK
