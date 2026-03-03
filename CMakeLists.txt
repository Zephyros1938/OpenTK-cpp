cmake_minimum_required(VERSION 3.10)
project(OpenTK_CPP VERSION 1.0.0 LANGUAGES CXX)

# 1. Create a header-only (INTERFACE) library
add_library(OpenTK INTERFACE)

# 2. Add the include directory to the search path
# BUILD_INTERFACE: Used when compiling inside this folder (for tests/examples)
# INSTALL_INTERFACE: Used when someone installs your lib via 'make install'
target_include_directories(OpenTK INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 3. Set C++ standard (Header-only needs this to be INTERFACE too)
target_compile_features(OpenTK INTERFACE cxx_std_23)

# --- OPTIONAL: Unit Testing / Example ---
# If you have a file in src/main.cpp to test your library:
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
  add_executable(test_app src/main.cpp)
  target_link_libraries(test_app PRIVATE OpenTK)
endif()
