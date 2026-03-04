#!/bin/bash

DATA_FILE="tests.txt"

# 1. Check if an argument was provided
if [ -z "$1" ]; then
  echo "Usage: ./test.sh [test_name]"
  echo "Available tests:"
  awk '{print "  - " $1}' "$DATA_FILE"
  exit 1
fi

TEST_NAME=$1

# 2. Find the file path associated with the name
TEST_PATH=$(grep "^$TEST_NAME " "$DATA_FILE" | awk '{print $2}')

if [ -z "$TEST_PATH" ]; then
  echo "Error: Test '$TEST_NAME' not found in $DATA_FILE."
  exit 1
fi

echo "Configuring $TEST_NAME ($TEST_PATH)..."

# 3. Build process
mkdir -p build
# Pass the source path to CMake so it knows what to compile
cmake -S . -B build -DTEST_SOURCE="$TEST_PATH" -DTEST_NAME="$TEST_NAME" -DVERBOSE=ON
cmake --build build

# 4. Run the specific binary
if [ $? -eq 0 ]; then
  echo "--- Running $TEST_NAME ---"
  ./build/"$TEST_NAME"
else
  echo "Build failed."
fi
