cmake_minimum_required(VERSION 3.24)
project(cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Apple Silicon Homebrew installs Google Test under /opt/homebrew.
if(EXISTS "/opt/homebrew")
  list(PREPEND CMAKE_PREFIX_PATH "/opt/homebrew")
endif()

find_package(GTest REQUIRED)

add_library(cpp_lib src/add.cpp)
target_include_directories(cpp_lib PUBLIC include)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE cpp_lib)

enable_testing()
file(GLOB test_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*_test.cpp")
add_executable(cpp_tests ${test_sources})
target_link_libraries(cpp_tests PRIVATE cpp_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cpp_tests)
