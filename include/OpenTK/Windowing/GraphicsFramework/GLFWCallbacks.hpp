#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/ConnectedState.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/ErrorCode.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/InputAction.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/KeyModifiers.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/Keys.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/MouseButton.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Monitor.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Window.hpp>
#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
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
} // namespace OpenTK::windowing::graphicsframework
