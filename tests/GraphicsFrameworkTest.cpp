#include <iostream>
#include <vector>

#include "OpenTK/Windowing/GraphicsFramework/GLFW.hpp"

using namespace OpenTK::Windowing::GraphicsFramework;

int main() {
  // 1. Initialize GLFW
  std::cout << "[LOG] Initializing GLFW..." << std::endl;
  if (!GLFW::Init()) {
    std::cerr << "[ERROR] Failed to initialize GLFW" << std::endl;
    return -1;
  }
  std::cout << "[LOG] GLFW initialized successfully." << std::endl;

  // 2. Set window hints
  std::cout << "[LOG] Setting window hints..." << std::endl;
  GLFW::DefaultWindowHints();
  GLFW::WindowHint(WindowHintBool::Resizable, true);
  GLFW::WindowHint(WindowHintBool::Visible, true);

  // Set OpenGL version 3.3 Core
  GLFW::WindowHint(WindowHintInt::ContextVersionMajor, 3);
  GLFW::WindowHint(WindowHintInt::ContextVersionMinor, 3);
  GLFW::WindowHint(WindowHintOpenGlProfile::OpenGlProfile, OpenGlProfile::Core);
  std::cout << "[LOG] OpenGL 3.3 Core profile hints set." << std::endl;

  // 3. Create a Window
  std::cout << "[LOG] Attempting to create window..." << std::endl;
  // Note: monitor and share are dereferenced in GLFW.hpp as *monitor and
  // *share. Passing nullptr here will crash if your Window/Monitor wrapper
  // classes do not handle null pointers in their dereference operators (*).
  Window *window =
      GLFW::CreateWindow(800, 600, "OpenTK C++ Binding Test", nullptr, nullptr);

  if (!window) {
    std::cerr << "[ERROR] Failed to create GLFW window" << std::endl;
    GLFW::Terminate();
    return -1;
  }
  std::cout << "[LOG] Window created successfully at memory address: " << window
            << std::endl;

  // 4. Make the context current
  std::cout << "[LOG] Making OpenGL context current..." << std::endl;
  GLFW::MakeContextCurrent(window);
  std::cout << "[LOG] Context is now current." << std::endl;

  // 5. Query Monitor Information
  std::cout << "[LOG] Querying monitor information..." << std::endl;
  int monitorCount = 0;
  Monitor **monitors = GLFW::GetMonitorsRaw(&monitorCount);

  if (monitors != nullptr && monitorCount > 0) {
    std::cout << "[LOG] Detected " << monitorCount << " monitor(s)."
              << std::endl;

    // Safety check before calling GetMonitorName
    if (monitors[0] != nullptr) {
      std::cout << "[LOG] Primary Monitor Name: "
                << GLFW::GetMonitorName(monitors[0]) << std::endl;
    }
  } else {
    std::cout << "[WARN] No monitors detected or GetMonitorsRaw returned null."
              << std::endl;
  }

  std::cout << "[LOG] GLFW Version String: " << GLFW::GetVersionString()
            << std::endl;

  // 6. Main Loop
  std::cout << "[LOG] Entering main loop..." << std::endl;
  while (!GLFW::WindowShouldClose(window)) {

    // Input check
    if (GLFW::GetKey(window, Keys::Escape) == InputAction::Press) {
      std::cout << "[LOG] Escape pressed. Closing window..." << std::endl;
      GLFW::SetWindowShouldClose(window, true);
    }

    // 7. Swap buffers and poll events
    GLFW::SwapBuffers(window);
    GLFW::PollEvents();
  }
  std::cout << "[LOG] Main loop exited." << std::endl;

  // 8. Cleanup
  std::cout << "[LOG] Cleaning up resources..." << std::endl;

  // Cleanup monitors array if it was allocated
  if (monitors) {
    for (int i = 0; i < monitorCount; ++i) {
      delete monitors[i];
    }
    delete[] monitors;
    std::cout << "[LOG] Monitor metadata cleaned up." << std::endl;
  }

  GLFW::DestroyWindow(window);
  delete window; // Assuming Window was allocated with 'new' in
                 // GLFW::CreateWindow

  std::cout << "[LOG] Terminating GLFW..." << std::endl;
  GLFW::Terminate();

  std::cout << "[LOG] Program exited gracefully." << std::endl;
  return 0;
}
