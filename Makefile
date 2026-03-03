# Compiler and Flags
CXX      := g++
CXXFLAGS := -std=c++23 -Wall -Wextra

# THE FIX: Add the include directory to the search path
# This allows #include <OpenTK/windowing/...>
CPPFLAGS := -Iinclude

# Directory Structure
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

# Find all .cpp files in src (adjust if your source files are named differently)
SOURCES  := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS  := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET   := $(BIN_DIR)/mylibrary_test

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
