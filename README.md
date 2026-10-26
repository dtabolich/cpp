# cpp

Small C++ project for Apple Silicon. CMake builds the app and the tests. Google Test 1.18.0 is downloaded on the first configure.

The binary is arm64. It runs on macOS 11 or newer, which covers every M1 Mac.

## Prerequisites

Follow these steps on the other Mac. The Mac needs Apple Silicon and macOS 11 or newer. Finish each installer before you start the next step.

### 1. Install the Xcode command line tools

This step installs Git, SSH, and Apple clang.

```bash
xcode-select --install
```

Wait until the installer finishes. If the tools are already present, the command tells you that.

### 2. Install Homebrew

Skip this step when `brew` already runs.

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Homebrew installs under `/opt/homebrew` on Apple Silicon. Add it to your shell:

```bash
echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
eval "$(/opt/homebrew/bin/brew shellenv)"
```

Open a new terminal after this step.

### 3. Install CMake

This project needs CMake 3.24 or newer.

```bash
brew install cmake
cmake --version
```

### 4. Check GitHub SSH

The repository is private. This check must succeed before you clone:

```bash
ssh -T git@github.com
```

GitHub prints a success line and the command exits with status 1. That result means access works.

If the check prints `Permission denied`, create a key. The command asks for a file path and a passphrase. Press Enter to accept the default path. Type a passphrase.

```bash
ssh-keygen -t ed25519 -C "dtabolich@gmail.com"
```

Save the key in the macOS keychain. Run these commands once:

```bash
mkdir -p ~/.ssh
chmod 700 ~/.ssh
touch ~/.ssh/config
chmod 600 ~/.ssh/config
cat >> ~/.ssh/config <<'EOF'
Host github.com
  AddKeysToAgent yes
  UseKeychain yes
  IdentityFile ~/.ssh/id_ed25519
EOF
ssh-add --apple-use-keychain ~/.ssh/id_ed25519
pbcopy < ~/.ssh/id_ed25519.pub
```

Open https://github.com/settings/ssh/new and paste the key. Run `ssh -T git@github.com` again.

### 5. Clone the repository

```bash
git clone git@github.com:dtabolich/cpp.git
cd cpp
```

Skip this step when you are already in the cloned project folder.

## Build and run

Run this from the project folder. The first configure downloads Google Test, so the Mac needs a network connection. The app prints `5` when the build works.

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
