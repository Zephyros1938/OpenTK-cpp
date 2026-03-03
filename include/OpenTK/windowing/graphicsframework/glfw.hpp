#pragma once

#include "cursor.hpp"
#include "enum/ANGLEplatformtype.hpp"
#include "enum/clientapi.hpp"
#include "enum/contextapi.hpp"
#include "enum/cursormodevalue.hpp"
#include "enum/cursorshape.hpp"
#include "enum/cursorstateattribute.hpp"
#include "enum/errorcode.hpp"
#include "enum/inithintANGLEplatformtype.hpp"
#include "enum/inithintbool.hpp"
#include "enum/inithintint.hpp"
#include "enum/inithintplatform.hpp"
#include "enum/inputaction.hpp"
#include "enum/joystickhats.hpp"
#include "enum/joystickinputaction.hpp"
#include "enum/lockkeymodattribute.hpp"
#include "enum/mousebutton.hpp"
#include "enum/openglprofile.hpp"
#include "enum/platform.hpp"
#include "enum/rawmousemotionattribute.hpp"
#include "enum/releasebehavior.hpp"
#include "enum/robustness.hpp"
#include "enum/stickyattributes.hpp"
#include "enum/windowattribute.hpp"
#include "enum/windowattributegetbool.hpp"
#include "enum/windowattributegetclientapi.hpp"
#include "enum/windowattributegetcontextapi.hpp"
#include "enum/windowattributegetopenglprofile.hpp"
#include "enum/windowattributegetreleasebehavior.hpp"
#include "enum/windowattributegetrobustness.hpp"
#include "enum/windowhintbool.hpp"
#include "enum/windowhintclientapi.hpp"
#include "enum/windowhintcontextapi.hpp"
#include "enum/windowhintint.hpp"
#include "enum/windowhintopenglprofile.hpp"
#include "enum/windowhintreleasebehavior.hpp"
#include "enum/windowhintrobustness.hpp"
#include "enum/windowhintstring.hpp"
#include "gammaramp.hpp"
#include "glfwcallbacks.hpp"
#include "image.hpp"
#include "input/gamepadstate.hpp"
#include "monitor.hpp"
#include "videomode.hpp"
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <OpenTK/Ported/intptr.hpp>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>
#include <string>
template <typename T> using ReadOnlySpan = std::span<const T>;

using IntPtr = OpenTK::Ported::IntPtr;

namespace OpenTK {

namespace windowing {
namespace graphicsframework {
class GLFW {
public:
  const int DontCare = -1;
  const int AnyPosition = 0x80000000;
  static bool Init() { return glfwInit() == GLFW_TRUE; }
  static void Terminate() { glfwTerminate(); }
  static void InitHint(graphicsframework::InitHintBool h, bool v) {
    glfwInitHint((int)h, v ? GLFW_TRUE : GLFW_FALSE);
  }
  static void InitHint(graphicsframework::InitHintInt h, int v) {
    glfwInitHint((int)h, v);
  }
  static void InitHint(graphicsframework::InitHintPlatform h,
                       graphicsframework::Platform v) {
    glfwInitHint((int)h, (int)v);
  }
  static void InitHint(graphicsframework::InitHintANGLEPlatformType h,
                       graphicsframework::ANGLEPlatformType v) {
    glfwInitHint((int)h, (int)v);
  }
  static void
  InitAllocator(windowing::graphicsframework::GLFWallocator *allocator) {

    glfwInitAllocator(reinterpret_cast<const ::GLFWallocator *>(allocator));
  }
  /*static void InitVulkanLoader(uint32_t *loader) {
    glfwInitVulkanLoader(loader);
  }*/
  static void GetVersion(uint32_t *major, uint32_t *minor, uint32_t *revision) {
    int localMajor, localMinor, localRevision;
    glfwGetVersion(&localMajor, &localMinor, &localRevision);
    *major = localMajor;
    *minor = localMinor;
    *revision = localRevision;
  }
  static std::string GetVersionString() { return glfwGetVersionString(); }
  static const char *GetVersionStringRaw() { return glfwGetVersionString(); }
  static ErrorCode GetError(std::string description) {
    const char *desc;
    auto code = glfwGetError(&desc);
    description = desc;
    return ErrorCode(code);
  }
  static ErrorCode
  GetErrorRaw(const char *description) { // INFO: no idea if this does anything,
                                         // just copying the original function.
    const char *desc;
    auto code = glfwGetError(&desc);
    description = desc;
    return ErrorCode(code);
  }
  static Platform GetPlatform() { return Platform(glfwGetPlatform()); }
  static bool PlatformSupported(Platform platform) {
    return glfwPlatformSupported((int)platform) == GLFW_TRUE;
  }
  static Monitor **GetMonitorsRaw(int *count) {
    GLFWmonitor **glfwMonitors = glfwGetMonitors(count);
    Monitor **monitors = new Monitor *[*count];
    for (int n = 0; n < *count; n++) {
      monitors[n] = new Monitor(glfwMonitors[n]);
    }
    return monitors;
  }
  static Monitor **GetMonitors() {
    int count;
    auto ptr = GetMonitorsRaw(&count);
    if (!ptr)
      return nullptr;
    auto array = new Monitor *[count];
    for (int i = 0; i < count; i++)
      array[i] = ptr[i];
    return array;
  }
  static void GetMonitorPos(Monitor *m, int *x, int *y) {
    glfwGetMonitorPos(*m, x, y);
  }
  static void GetMonitorWorkarea(Monitor *m, int *x, int *y, int *width,
                                 int *height) {
    glfwGetMonitorWorkarea(*m, x, y, width, height);
  }
  static void GetMonitorPhysicalSize(Monitor *m, int *width, int *height) {
    glfwGetMonitorPhysicalSize(*m, width, height);
  }
  static void GetMonitorContentScale(Monitor *m, float *xScale, float *yScale) {
    glfwGetMonitorContentScale(*m, xScale, yScale);
  }
  static std::string GetMonitorName(Monitor *m) {
    return glfwGetMonitorName(*m);
  }
  static const char *GetMonitorNameRaw(Monitor *m) {
    return glfwGetMonitorName(*m);
  }
  static void SetMonitorUserPointer(Monitor *m, void *pointer) {
    glfwSetMonitorUserPointer(*m, pointer);
  }
  static void *GetMonitorUserPointer(Monitor *m) {
    return glfwGetMonitorUserPointer(*m);
  }
  static VideoMode *GetVideoModesRaw(Monitor *m, int *count) {
    const GLFWvidmode *glfwVideoModes = glfwGetVideoModes(*m, count);
    VideoMode *videoModes = new VideoMode[*count];
    for (int n = 0; n < *count; n++) {
      videoModes[n] = *new VideoMode(&glfwVideoModes[n]);
    }
    return videoModes;
  }
  static VideoMode *GetVideoModes(Monitor *m) {
    int count;
    auto ptr = GetVideoModesRaw(m, &count);
    if (!ptr)
      return nullptr;
    auto array = new VideoMode[count];
    for (int i = 0; i < count; i++) {
      array[i] = ptr[i];
    }
    return array;
  }
  static void SetGamma(Monitor *m, float gamma) { glfwSetGamma(*m, gamma); }
  static GammaRamp *GetGammaRamp(Monitor *m) {
    return new GammaRamp(glfwGetGammaRamp(*m));
  }
  static void SetGammaRamp(Monitor *m, GammaRamp *ramp) {
    glfwSetGammaRamp(*m, (GLFWgammaramp *)ramp);
  }
  static void DefaultWindowHints() { glfwDefaultWindowHints(); }
  static void WindowHint(WindowHintString hint, std::string value) {
    glfwWindowHintString((int)hint, value.c_str());
  }
  static void WindowHintRaw(WindowHintString hint, const char *value) {
    glfwWindowHintString((int)hint, value);
  }
  static void SetWindowSizeLimits(Window *w, int minWidth, int minHeight,
                                  int maxWidth, int maxHeight) {
    glfwSetWindowSizeLimits(*w, minWidth, minHeight, maxWidth, maxHeight);
  }
  static void SetWindowAspectRatio(Window *w, int numer, int denom) {
    glfwSetWindowAspectRatio(*w, numer, denom);
  }
  static void GetWindowFrameSize(Window *w, int *left, int *top, int *right,
                                 int *bottom) {
    int l, t, r, b;
    glfwGetWindowFrameSize(*w, &l, &t, &r, &b);
    *left = l;
    *top = t;
    *right = r;
    *bottom = b;
  }
  static void GetWindowContentScale(Window *w, float *xScale, float *yScale) {
    float x, y;
    glfwGetWindowContentScale(*w, &x, &y);
    *xScale = x;
    *yScale = y;
  }
  static float GetWindowOpacity(Window *w) { return glfwGetWindowOpacity(*w); }
  static void SetWindowOpacity(Window *w, float opacity) {
    glfwSetWindowOpacity(*w, opacity);
  }
  static void RequestWindowAttention(Window *w) {
    glfwRequestWindowAttention(*w);
  }
  static void SetWindowAttrib(Window *w, WindowAttribute a, bool value) {
    glfwSetWindowAttrib(*w, (int)a, value ? GLFW_TRUE : GLFW_FALSE);
  }
  static bool RawMouseMotionSupported() {
    return glfwRawMouseMotionSupported() == GLFW_TRUE;
  }
  static std::string GetKeyName(Keys key, int scancode) {
    return glfwGetKeyName((int)key, scancode);
  }
  static const char *GetKeyNameRaw(Keys key, int scancode) {
    return glfwGetKeyName((int)key, scancode);
  }
  static int GetKeyScancode(Keys key) { return glfwGetKeyScancode((int)key); }
  static InputAction GetKey(Window *w, Keys key) {
    return InputAction(glfwGetKey(*w, (int)key));
  }
  static InputAction GetMouseButton(Window *w, MouseButton button) {
    return InputAction(glfwGetMouseButton(*w, (int)button));
  }
  // CURSOR
  static void GetCursorPos(Window *w, double *xPos, double *yPos) {
    double x, y;
    glfwGetCursorPos(*w, &x, &y);
    *xPos = x;
    *yPos = y;
  }
  static void GetCursorPosRaw(Window *w, double *xPos, double *yPos) {
    glfwGetCursorPos(*w, xPos, yPos);
  }
  static void SetCursorPos(Window *w, double xPos, double yPos) {
    glfwSetCursorPos(*w, xPos, yPos);
  }
  static Cursor *CreateCursor(Image image, int xHot, int yHot) {
    Image *ptr = &image;
    return CreateCursorRaw(*ptr, xHot, yHot);
  }
  static Cursor *CreateCursorRaw(Image image, int xHot, int yHot) {
    return new Cursor(glfwCreateCursor(image, xHot, yHot));
  }
  static Cursor *CreateStandardCursor(CursorShape shape) {
    return new Cursor(glfwCreateStandardCursor((int)shape));
  }
  static void DestroyCursor(Cursor *cursor) { glfwDestroyCursor(*cursor); }
  static void SetCursor(Window *w, Cursor *cursor) {
    glfwSetCursor(*w, *cursor);
  }
  // JOYSTICK
  static bool JoyStickPresent(int jid) {
    return glfwJoystickPresent(jid) == GLFW_TRUE;
  }
  static ReadOnlySpan<float> GetJoystickAxes(int jid) {
    int count;
    auto ptr = GetJoystickAxesRaw(jid, &count);
    if (ptr) {
      return {ptr, static_cast<size_t>(count)};
    }
    return {};
  }
  static const float *GetJoystickAxesRaw(int jid, int *count) {
    return glfwGetJoystickAxes(jid, count);
  }
  static ReadOnlySpan<JoystickInputAction> GetJoystickButtons(int jid) {
    int count;
    auto ptr = GetJoystickButtonsRaw(jid, &count);
    return (ptr != nullptr)
               ? ReadOnlySpan<JoystickInputAction>{ptr,
                                                   static_cast<std::size_t>(
                                                       count)}
               : ReadOnlySpan<JoystickInputAction>{};
  }
  static const JoystickInputAction *GetJoystickButtonsRaw(int jid, int *count) {
    return (JoystickInputAction *)glfwGetJoystickButtons(jid, count);
  }
  static ReadOnlySpan<JoystickHats> GetJoystickHats(int jid) {
    int count;
    auto ptr = GetJoystickHatsRaw(jid, &count);
    return (ptr != nullptr)
               ? ReadOnlySpan<JoystickHats>{ptr,
                                            static_cast<std::size_t>(count)}
               : ReadOnlySpan<JoystickHats>{};
  }
  static const JoystickHats *GetJoystickHatsRaw(int jid, int *count) {
    return (JoystickHats *)glfwGetJoystickHats(jid, count);
  }
  static std::string GetJoystickName(int jid) {
    return glfwGetJoystickName(jid);
  }
  static const char *GetJoystickNameRaw(int jid) {
    return glfwGetJoystickName(jid);
  }
  static std::string GetJoystickGUID(int jid) {
    return glfwGetJoystickGUID(jid);
  }
  static const char *GetJoystickGUIDRaw(int jid) {
    return glfwGetJoystickGUID(jid);
  }
  static void SetJoystickUserPointer(int jid, void *ptr) {
    glfwSetJoystickUserPointer(jid, ptr);
  }
  static void *GetJoystickUserPointer(int jid) {
    return glfwGetJoystickUserPointer(jid);
  }
  static bool JoystickIsGamepad(int jid) { return glfwJoystickIsGamepad(jid); }
  // GAMEPAD
  static bool UpdateGamepadMappings(std::string newMapping) {
    auto ptr = newMapping.c_str();
    return glfwUpdateGamepadMappings(ptr) == GLFW_TRUE;
  }
  static bool UpdateGamepadMappingsRaw(const char *newMapping) {
    return glfwUpdateGamepadMappings(newMapping) == GLFW_TRUE;
  }
  static std::string GetGamepadName(int jid) { return glfwGetGamepadName(jid); }
  static const char *GetGamepadNameRaw(int jid) {
    return glfwGetGamepadName(jid);
  }
  static bool GetGamepadState(int jid, GamepadState *state) {
    return glfwGetGamepadState(jid, *state) ==
           GLFW_TRUE; // this is the same as `GetGamepadStateRaw` since this
                      // isnt c# lol
  }
  static bool GetGamepadStateRaw(int jid, GamepadState *state) {
    return glfwGetGamepadState(jid, *state) == GLFW_TRUE;
  }
  // TIME
  static double GetTime() { return glfwGetTime(); }
  static void SetTime(double time) { glfwSetTime(time); }
  static long GetTimerValue() { return glfwGetTimerValue(); }
  static long GetTimerFrequency() { return glfwGetTimerFrequency(); }
  static Window *GetCurrentContext() {
    return new Window(glfwGetCurrentContext());
  }
  static void SwapBuffers(Window *w) { glfwSwapBuffers(*w); }
  static bool ExtensionsSupported(std::string extensionName) {
    auto ptr = extensionName.c_str();
    return glfwExtensionSupported(ptr) == GLFW_TRUE;
  }
  static IntPtr GetProcAddress(std::string proc) {
    return (IntPtr)glfwGetProcAddress(proc.c_str());
  }
  static IntPtr GetProcAddressRaw(const char *proc) {
    return (IntPtr)glfwGetProcAddress(proc);
  }
  static bool ExtensionsSupportedRaw(const char *extensionName) {
    return glfwExtensionSupported(extensionName) == GLFW_TRUE;
  }
  static Window *CreateWindow(int width, int height, std::string title,
                              Monitor *monitor, Window *share) {
    auto ptr = title.c_str();
    return new Window(glfwCreateWindow(width, height, ptr, *monitor, *share));
  }
  static Window *CreateWindowRaw(int width, int height, const char *title,
                                 Monitor *monitor, Window *share) {
    return new Window(glfwCreateWindow(width, height, title, *monitor, *share));
  }
  static void DestroyWindow(Window *w) { glfwDestroyWindow(*w); }
  static void FocusWindow(Window *w) { glfwFocusWindow(*w); }
  static std::string GetClipboardString(Window *w) {
    return glfwGetClipboardString(*w);
  }
  static const char *GetClipboardStringRaw(Window *w) {
    return glfwGetClipboardString(*w);
  }
  static void GetFramebufferSize(Window *w, int *width, int *height) {
    int w_, h_;
    glfwGetFramebufferSize(*w, &w_, &h_);
    *width = w_;
    *height = h_;
  }
  static void GetFramebufferSizeRaw(Window *w, int *width, int *height) {
    glfwGetFramebufferSize(*w, width, height);
  }
  static bool GetInputMode(Window *w, StickyAttributes mode) {
    return glfwGetInputMode(*w, (int)mode) == GLFW_TRUE;
  }
  static bool GetInputMode(Window *w, CursorStateAttribute mode) {
    return glfwGetInputMode(*w, (int)mode) == GLFW_TRUE;
  }
  static bool GetInputMode(Window *w, LockKeyModAttribute mode) {
    return glfwGetInputMode(*w, (int)mode) == GLFW_TRUE;
  }
  static bool GetInputMode(Window *w, RawMouseMotionAttribute mode) {
    return glfwGetInputMode(*w, (int)mode) == GLFW_TRUE;
  }
  static Monitor *GetPrimaryMonitor() {
    return new Monitor(glfwGetPrimaryMonitor());
  }
  static VideoMode *GetVideoMode(Monitor *m) {
    return new VideoMode(glfwGetVideoMode(*m));
  }
  static bool GetWindowAttrib(Window *w, WindowAttributeGetBool attr) {
    return glfwGetWindowAttrib(*w, (int)attr);
  }
  static ClientApi GetWindowAttrib(Window *w,
                                   WindowAttributeGetClientApi attr) {
    return ClientApi(glfwGetWindowAttrib(*w, (int)attr));
  }
  static ContextApi GetWindowAttrib(Window *w,
                                    WindowAttributeGetContextApi attr) {
    return ContextApi(glfwGetWindowAttrib(*w, (int)attr));
  }
  static OpenGlProfile GetWindowAttrib(Window *w,
                                       WindowAttributeGetOpenGlProfile attr) {
    return OpenGlProfile(glfwGetWindowAttrib(*w, (int)attr));
  }
  static ReleaseBehavior
  GetWindowAttrib(Window *w, WindowAttributeGetReleaseBehavior attr) {
    return ReleaseBehavior(glfwGetWindowAttrib(*w, (int)attr));
  }
  static Robustness GetWindowAttrib(Window *w,
                                    WindowAttributeGetRobustness attr) {
    return Robustness(glfwGetWindowAttrib(*w, (int)attr));
  }
  static void SetWindowUserPointer(Window *w, void *pointer) {
    glfwSetWindowUserPointer(*w, pointer);
  }
  static void GetWindowSize(Window *w, int *width, int *height) {
    int w_, h;
    glfwGetWindowSize(*w, &w_, &h);
    *width = w_;
    *height = h;
  }
  static void GetWindowSizeRaw(Window *w, int *width, int *height) {
    glfwGetWindowSize(*w, width, height);
  }
  static void GetWindowPos(Window *w, int *x, int *y) {
    int px, py;
    glfwGetWindowPos(*w, &px, &py);
    *x = px;
    *y = py;
  }
  static void GetWindowPosRaw(Window *w, int *x, int *y) {
    glfwGetWindowPos(*w, x, y);
  }
  static Monitor *GetWindowMonitor(Window *w) {
    return new Monitor(glfwGetWindowMonitor(*w));
  }
  static void HideWindow(Window *w) { glfwHideWindow(*w); }
  static void IconifyWindow(Window *w) { glfwIconifyWindow(*w); }
  static void MakeContextCurrent(Window *w) { glfwMakeContextCurrent(*w); }
  static void MaximizeWindow(Window *w) { glfwMaximizeWindow(*w); }
  static IntPtr
  SetWindowMaximizeCallback(Window *w,
                            GLFWCallbacks::WindowMaximizeCallback cb) {
    return (IntPtr)glfwSetWindowMaximizeCallback(
        *w, (GLFWwindowmaximizefun)cb);
  }
  static IntPtr
  SetFrameBufferSizeCallback(Window *w,
                             GLFWCallbacks::FramebufferSizeCallback cb) {
    return (IntPtr)glfwSetFramebufferSizeCallback(
        *w, (GLFWframebuffersizefun)cb);
  }
  static void PollEvents() { glfwPollEvents(); }
  static void PostEmptyEvent() { glfwPostEmptyEvent(); }
  static void RestoreWindow(Window *w) { glfwRestoreWindow(*w); }
  static IntPtr SetCharCallback(Window *w,
                                      GLFWCallbacks::CharCallback cb) {
    return (IntPtr)glfwSetCharCallback(*w, (GLFWcharfun)cb);
  }
  static IntPtr SetCharModsCallback(Window *w,
                                          GLFWCallbacks::CharModsCallback cb) {
    return (IntPtr)glfwSetCharModsCallback(*w, (GLFWcharmodsfun)cb);
  }
  static void SetClipboardString(Window *w, std::string data) {
    auto ptr = data.c_str();
    glfwSetClipboardString(*w, ptr);
  }
  static void SetClipboardStringRaw(Window *w, const char *data) {
    glfwSetClipboardString(*w, data);
  }
  static IntPtr
  SetCursorEnterCallback(Window *w, GLFWCallbacks::CursorEnterCallback cb) {
    return (IntPtr)glfwSetCursorEnterCallback(*w, (GLFWcursorenterfun)cb);
  }
  static IntPtr
  SetCursorPosCallback(Window *w, GLFWCallbacks::CursorPosCallback cb) {
    return (IntPtr)glfwSetCursorPosCallback(*w, (GLFWcursorposfun)cb);
  }
  static IntPtr SetDropCallback(Window *w,
                                      GLFWCallbacks::DropCallback cb) {
    return (IntPtr)glfwSetDropCallback(*w, (GLFWdropfun)cb);
  }
  static IntPtr SetErrorCallback(GLFWCallbacks::ErrorCallback cb) {
    return (IntPtr)glfwSetErrorCallback((GLFWerrorfun)cb);
  }
  static void SetInputMode(Window *w, CursorStateAttribute mode,
                           CursorModeValue value) {
    glfwSetInputMode(*w, (int)mode, (int)value);
  }
  static void SetInputMode(Window *w, StickyAttributes mode, bool value) {
    glfwSetInputMode(*w, (int)mode, value ? GLFW_TRUE : GLFW_FALSE);
  }
  static void SetInputMode(Window *w, LockKeyModAttribute mode, bool value) {
    glfwSetInputMode(*w, (int)mode, value ? GLFW_TRUE : GLFW_FALSE);
  }
  static void SetInputMode(Window *w, RawMouseMotionAttribute mode,
                           bool value) {
    glfwSetInputMode(*w, (int)mode, value ? GLFW_TRUE : GLFW_FALSE);
  }
  static IntPtr SetJoystickCallback(GLFWCallbacks::JoystickCallback cb) {
    return (IntPtr)glfwSetJoystickCallback((GLFWjoystickfun)cb);
  }
  static IntPtr SetKeyCallback(Window *w, GLFWCallbacks::KeyCallback cb) {
    return (IntPtr)glfwSetKeyCallback(*w, (GLFWkeyfun)cb);
  }
  static IntPtr SetScrollCallback(Window *w,
                                        GLFWCallbacks::ScrollCallback cb) {
    return (IntPtr)glfwSetScrollCallback(*w, (GLFWscrollfun)cb);
  }
  static IntPtr SetMonitorCallback(GLFWCallbacks::MonitorCallback cb) {
    return (IntPtr)glfwSetMonitorCallback((GLFWmonitorfun)cb);
  }
  static IntPtr
  SetMouseButtonCallback(Window *w, GLFWCallbacks::MouseButtonCallback cb) {
    return (IntPtr)glfwSetMouseButtonCallback(*w, (GLFWmousebuttonfun)cb);
  }
  static IntPtr
  SetWindowCloseCallback(Window *w, GLFWCallbacks::WindowCloseCallback cb) {
    return (IntPtr)glfwSetWindowCloseCallback(*w, (GLFWwindowclosefun)cb);
  }
  static IntPtr
  SetWindowFocusCallback(Window *w, GLFWCallbacks::WindowFocusCallback cb) {
    return (IntPtr)glfwSetWindowFocusCallback(*w, (GLFWwindowfocusfun)cb);
  }
  static void SetWindowIcon(Window *w, ReadOnlySpan<Image> images) {
    const Image *ptr = images.data();
    auto a = *ptr;
    glfwSetWindowIcon(*w, images.size(),
                      a); // TODO: fix this i hate this code lmfao
  }
  static void SetWindowIconRaw(Window *w, int count, Image *images) {
    glfwSetWindowIcon(*w, count, *images);
  }
  static IntPtr
  SetWindowIconifyCallback(Window *w, GLFWCallbacks::WindowIconifyCallback cb) {
    return (IntPtr)glfwSetWindowIconifyCallback(*w,
                                                      (GLFWwindowiconifyfun)cb);
  }
  static void SetWindowMonitor(Window *w, Monitor *m, int x, int y, int width,
                               int height, int refreshRate) {
    glfwSetWindowMonitor(*w, *m, x, y, width, height, refreshRate);
  }
  static void SetWindowPos(Window *w, int x, int y) {
    glfwSetWindowPos(*w, x, y);
  }
  static IntPtr
  SetWindowPosCallback(Window *w, GLFWCallbacks::WindowPosCallback cb) {
    return (IntPtr)glfwSetWindowPosCallback(*w, (GLFWwindowposfun)cb);
  }
  static IntPtr
  SetWindowRefreshCallback(Window *w, GLFWCallbacks::WindowRefreshCallback cb) {
    return (IntPtr)glfwSetWindowRefreshCallback(*w,
                                                      (GLFWwindowrefreshfun)cb);
  }
  static void SetWindowSize(Window *w, int width, int height) {
    glfwSetWindowSize(*w, width, height);
  }
  static IntPtr
  SetWindowSiezCallback(Window *w, GLFWCallbacks::WindowSizeCallback cb) {
    return (IntPtr)glfwSetWindowSizeCallback(*w, (GLFWwindowsizefun)cb);
  }
  static void SetWindowShouldClose(Window *w, bool value) {
    glfwSetWindowShouldClose(*w, value ? GLFW_TRUE : GLFW_FALSE);
  }
  static const char *GetWindowTitleRaw(Window *w) {
    return glfwGetWindowTitle(*w);
  }
  static std::string GetWindowTitle(Window *w) {
    return glfwGetWindowTitle(*w);
  }
  static void SetWindowTitle(Window *w, std::string title) {
    auto ptr = title.c_str();
    glfwSetWindowTitle(*w, ptr);
  }
  static void SetWindowTitleRaw(Window *w, const char *title) {
    glfwSetWindowTitle(*w, title);
  }
  static void ShowWindow(Window *w) { glfwShowWindow(*w); }
  static void SwapInterval(int interval) { glfwSwapInterval(interval); }
  static void WaitEvents() { glfwWaitEvents(); }
  static void WaitEventsTimeout(double timeout) {
    glfwWaitEventsTimeout(timeout);
  }
  static void WindowHint(WindowHintInt hint, int value) {
    glfwWindowHint((int)hint, value);
  }
  static void WindowHint(WindowHintBool hint, bool value) {
    glfwWindowHint((int)hint, value ? GLFW_TRUE : GLFW_FALSE);
  }
  static void WindowHint(WindowHintClientApi hint, ClientApi value) {
    glfwWindowHint((int)hint, (int)value);
  }
  static void WindowHint(WindowHintReleaseBehavior hint,
                         ReleaseBehavior value) {
    glfwWindowHint((int)hint, (int)value);
  }
  static void WindowHint(WindowHintContextApi hint, ContextApi value) {
    glfwWindowHint((int)hint, (int)value);
  }
  static void WindowHint(WindowHintRobustness hint, Robustness value) {
    glfwWindowHint((int)hint, (int)value);
  }
  static void WindowHint(WindowHintOpenGlProfile hint, OpenGlProfile value) {
    glfwWindowHint((int)hint, (int)value);
  }
  static bool WindowShouldClose(Window *w) {
    return glfwWindowShouldClose(*w) == GLFW_TRUE;
  }
  static bool VulkanSupported() { return glfwVulkanSupported() == GLFW_TRUE; }
  static const char **GetRequiredInstanceExtensionsRaw(unsigned int *count) {
    return glfwGetRequiredInstanceExtensions(count);
  }
  static std::string *GetRequiredInstanceExtensions() {
    unsigned int count;
    auto ptr = GetRequiredInstanceExtensionsRaw(&count);
    auto array = new std::string[count];
    for (size_t i = 0; i < count; i++) {
      array[i] = ptr[i];
    }
    return array;
  }
  // INFO: GLFW native support will not be ported as this is already handled
};
} // namespace graphicsframework
} // namespace windowing

} // namespace OpenTK
