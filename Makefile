# Makefile for Rayban Ray Tracer

# Variables
BUILD_DIR = build
CMAKE_BUILD_TYPE ?= Release
PROJECT_NAME = rayban
TEST_EXECUTABLE = rayban_tests

CLANG_TIDY ?= clang-tidy
ANALYSIS_BUILD_DIR = build-analysis

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
	@cmake -E make_directory $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) ..

# Build the main application
.PHONY: build
build: $(BUILD_DIR)/Makefile
	@echo "Building $(PROJECT_NAME)..."
	@cmake --build $(BUILD_DIR) --target $(PROJECT_NAME) --config $(CMAKE_BUILD_TYPE)
	@echo "Build complete! Executable: $(BUILD_DIR)/$(PROJECT_NAME)"

# Build and run tests
.PHONY: test
test: $(BUILD_DIR)/Makefile
	@echo "Building and running tests..."
	@cmake --build $(BUILD_DIR) --config $(CMAKE_BUILD_TYPE)
	@cd $(BUILD_DIR) && ctest --output-on-failure -C $(CMAKE_BUILD_TYPE)

# Build and run the main application
.PHONY: run
run: build
	@echo "Running $(PROJECT_NAME)..."
	@${RUN_CMD}

# Clean build directory
.PHONY: clean
clean:
	@echo "Cleaning build directory..."
	@cmake -E remove_directory $(BUILD_DIR)

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
	$(call require,clang-format)
	$(FORMAT_CMD)

# Check includes with clang-tidy (uses matching LLVM toolchain)
.PHONY: check-includes
check-includes:
	$(call require,$(CLANG_TIDY))
	@cmake -E make_directory $(ANALYSIS_BUILD_DIR)
	@cd $(ANALYSIS_BUILD_DIR) && CC="$(LLVM_BIN_DIR)clang" CXX="$(LLVM_BIN_DIR)clang++" \
		cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) ..
	@$(CLANG_TIDY) -checks='-*,misc-include-cleaner' --header-filter='include/.*' \
		-p $(ANALYSIS_BUILD_DIR) src/*.cpp tests/*.cpp

ifeq ($(OS),Windows_NT)
  NULL_DEV = nul
  WHICH = where
  EXE_EXT = .exe
  FORMAT_CMD = @powershell -Command "Get-ChildItem -Path src,include,tests -Recurse -Include *.cpp,*.h | ForEach-Object { clang-format -i $$_.FullName }"
  RUN_CMD = @$(BUILD_DIR)/$(CMAKE_BUILD_TYPE)/$(PROJECT_NAME)$(EXE_EXT)
else
  NULL_DEV = /dev/null
  WHICH = which
  EXE_EXT =
  FORMAT_CMD = @find src include tests -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i {} +
  RUN_CMD = @$(BUILD_DIR)/$(PROJECT_NAME)$(EXE_EXT)
endif

LLVM_BIN_DIR = $(dir $(shell $(WHICH) $(CLANG_TIDY) 2>$(NULL_DEV)))

ifeq ($(OS),Windows_NT)
  require = @$(WHICH) $(1) >$(NULL_DEV) 2>&1 || (echo Error: $(1) not found. && exit 1)
else
  require = @command -v $(1) >$(NULL_DEV) 2>&1 || { echo >&2 "Error: $(1) not found."; exit 1; }
endif
