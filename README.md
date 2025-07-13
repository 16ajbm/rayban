# Rayban

A C++ ray tracer inspired by the Ray Tracing in One Weekend series by Peter Shirley.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/16ajbm/rayban.git
   ```

2. Navigate to the project directory:

   ```bash
   cd rayban
   ```

3. Make sure you have the required dependencies:
   - CMake (3.15 or higher)
   - C++ compiler with C++17 support
   - Boost libraries (1.55 or higher)

4. Build and run:

   ```bash
   make run
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
