# Rayban

A C++ ray tracer built following the Pragmatic Programmer's [Ray Tracer Challenge](http://raytracerchallenge.com/).

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/16ajbm/rayban.git
   ```

2. Make sure you have the required dependencies:
   - CMake (3.15 or higher)
   - C++ compiler with C++17 support
   - Boost libraries (1.55 or higher)

3. Build and run:

   ```bash
   cd rayban && make run
   ```

### Optional: `clang-format`

If you want to format the code you can install `clang-format`, for example via:

```bash
# macOS
brew install clang-format

# Windows - LLVM (includes `clang-format`) via Chocolatey
choco install llvm -y
```

Then, you can format the code using:

```bash
make format
```

## Quick Start

The Makefile provides simple commands for common tasks:

```bash
# Build the project
make build

# Run tests
make test

# Build and run the application
make run

# Clean build files
make clean

# View all available commands
make help
```

## Manual Build (Alternative)

If you prefer to use CMake directly:

```bash
mkdir build
cd build
cmake ..
make
./rayban
```
