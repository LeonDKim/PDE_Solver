cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(PDE_SOLVER VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories (optional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(include)

# Add executable
add_executable(
    PDE_SOLVER 
    src/main.cpp
    src/Point2D.cpp
)