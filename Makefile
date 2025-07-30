# Makefile for Rayban Ray Tracer

# Variables
BUILD_DIR = build
CMAKE_BUILD_TYPE ?= Release
PROJECT_NAME = rayban
TEST_EXECUTABLE = rayban_tests

# Default target
.PHONY: all
all: build

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  build     - Build the main application"
	@echo "  test      - Build and run tests"
	@echo "  run       - Build and run the main application"
	@echo "  clean     - Clean build directory"
	@echo "  rebuild   - Clean and build"
	@echo "  debug     - Build in debug mode"
	@echo "  format    - Format code with clang-format"
	@echo "  help      - Show this help message"

# Create build directory and configure with CMake
$(BUILD_DIR)/Makefile:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) ..

# Build the main application
.PHONY: build
build: $(BUILD_DIR)/Makefile
	@echo "Building $(PROJECT_NAME)..."
	@cd $(BUILD_DIR) && $(MAKE) $(PROJECT_NAME)
	@echo "Build complete! Executable: $(BUILD_DIR)/$(PROJECT_NAME)"

# Build and run tests
.PHONY: test
test: $(BUILD_DIR)/Makefile
	@echo "Building and running tests..."
	@cd $(BUILD_DIR) && $(MAKE) $(TEST_EXECUTABLE)
	@cd $(BUILD_DIR) && ctest --output-on-failure

# Build and run the main application
.PHONY: run
run: build
	@echo "Running $(PROJECT_NAME)..."
	@./$(BUILD_DIR)/$(PROJECT_NAME)

# Clean build directory
.PHONY: clean
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

# Rebuild (clean + build)
.PHONY: rebuild
rebuild: clean build

# Debug build
.PHONY: debug
debug:
	@$(MAKE) build CMAKE_BUILD_TYPE=Debug

# Format code with clang-format
.PHONY: format
format fmt:
	@command -v clang-format >/dev/null 2>&1 || { echo >&2 "Error: clang-format not found. Please install it."; exit 1; }
	@clang-format -i src/* include/* tests/*