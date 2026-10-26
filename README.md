# cpp

Small C++ project for Apple Silicon. CMake builds the app and the tests. Google Test 1.18.0 is downloaded on the first configure.

The binary is arm64. It runs on macOS 11 or newer, which covers every M1 Mac.

## Requirements

Install the Xcode command line tools and CMake 3.24 or newer.

## Build and run

Run this from the project folder:

```bash
cmake -S . -B build && cmake --build build && ctest --test-dir build --output-on-failure && ./build/app
```

Later builds only need the compile and test steps:

```bash
cmake --build build && ctest --test-dir build --output-on-failure
```

## Add a test

Create a file under `tests/` whose name ends in `_test.cpp`. CMake picks it up on the next build. You do not edit `CMakeLists.txt`.

`tests/add_zero_test.cpp`:

```cpp
#include "add.hpp"

#include <gtest/gtest.h>

TEST(AddTest, AddsZero) {
  EXPECT_EQ(cpp::add(4, 0), 4);
}
```

Include any header from `include/`. The test binary links the library and Google Test.

## Layout

- `include/` and `src/` hold the library and the `app` executable.
- `tests/*_test.cpp` holds the Google Test files.
- `build/` is the local build tree. It is not committed.
