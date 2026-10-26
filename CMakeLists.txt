cmake_minimum_required(VERSION 3.24)

# Apple Silicon only. macOS 11 is the first release that shipped on M1.
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
  set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Apple Silicon")
  set(CMAKE_OSX_DEPLOYMENT_TARGET "11.0" CACHE STRING "Minimum macOS version")
endif()

project(cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.tar.gz
  URL_HASH SHA256=6e3191c1455468b3fc35a417fb565c1c5071aee1b7e7f85e30cf48a98d37d8b5
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(cpp_lib src/add.cpp)
target_include_directories(cpp_lib PUBLIC include)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE cpp_lib)

enable_testing()

# Every tests/*_test.cpp file is part of the cpp_tests binary.
file(GLOB CPP_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*_test.cpp")
if(NOT CPP_TEST_SOURCES)
  message(FATAL_ERROR "No test files in tests/. Name each file *_test.cpp.")
endif()

add_executable(cpp_tests ${CPP_TEST_SOURCES})
target_link_libraries(cpp_tests PRIVATE cpp_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(cpp_tests)
