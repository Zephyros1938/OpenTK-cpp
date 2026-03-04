cmake_minimum_required(VERSION 3.10)
project(OpenTK_CPP VERSION 1.0.0 LANGUAGES CXX)

# 1. Find GLFW (make sure libglfw3-dev is installed on your system)
find_package(glfw3 REQUIRED)

# 2. Create your header-only library
add_library(OpenTK INTERFACE)
target_include_directories(OpenTK INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(OpenTK INTERFACE cxx_std_26)

# 3. Build the test app
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
  add_executable(test_app src/main.cpp)

  # Link your wrapper AND the actual GLFW library
  target_link_libraries(test_app PRIVATE OpenTK glfw)
endif()
