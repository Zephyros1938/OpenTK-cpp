cmake_minimum_required(VERSION 3.10)
project(OpenTK_CPP VERSION 1.0.0 LANGUAGES CXX)

find_package(glfw3 REQUIRED)

add_library(OpenTK INTERFACE)
target_include_directories(OpenTK INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_options(OpenTK INTERFACE -std=c++2c)

if(NOT TEST_NAME)
  set(TEST_NAME "app")
endif()

if(NOT TEST_SOURCE)
  set(TEST_SOURCE "src/main.cpp")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_SOURCE}")
  if(VERBOSE)
    message(STATUS "-----------------------------------------------")
    message(STATUS " Building: ${TEST_NAME}")
    message(STATUS " Source:   ${TEST_SOURCE}")
    message(STATUS "-----------------------------------------------")
  endif()

  add_executable(${TEST_NAME} ${TEST_SOURCE})

  target_link_libraries(${TEST_NAME} PRIVATE OpenTK glfw)
else()
  message(FATAL_ERROR "Source file not found: ${TEST_SOURCE}")
endif()
