#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Configure and Build
cmake -S . -B build
cmake --build build

# Run the app if build was successful
if [ $? -eq 0 ]; then
    echo "--- Running test_app ---"
    ./build/test_app
else
    echo "Build failed."
fi
