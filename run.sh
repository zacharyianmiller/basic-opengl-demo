#!/bin/bash

# Reconfigure CMake project
cd scripts
./configure.sh

echo "Project configured."

# Build project
cd ../scripts
./build.sh

echo "Project built."

# Run project
echo "Running..."
./../build/basic-opengl-basic