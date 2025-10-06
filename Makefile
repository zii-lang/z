# Build directory
BUILD_DIR := build

# Default target
all: configure build

# Configure CMake
configure:
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DENABLE_TESTS=ON ..

# Build the project
build:
	cd $(BUILD_DIR) && cmake --build .

# Run tests
test: configure build
	cd $(BUILD_DIR) && ctest --output-on-failure

# Clean build
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all configure build test clean
