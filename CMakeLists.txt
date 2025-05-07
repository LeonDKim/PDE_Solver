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
    src/Polygon.cpp
    src/FDMGrid.cpp
)

# ---- GoogleTest Setup ----
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ---- Tests ----
add_executable(
    PDE_SOLVER_TESTS 
    src/Point2D.cpp
    tests/test_point2d.cc
)
target_link_libraries(PDE_SOLVER_TESTS GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(PDE_SOLVER_TESTS)