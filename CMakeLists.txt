cmake_minimum_required(VERSION 3.28.3)

# Your project settings
project(MyProject)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1  # Latest stable release as of Oct 2024
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Automatically gather application source files (excluding the test files)
file(GLOB_RECURSE APP_SOURCES
    src/*.cpp
    src/*.h
    lib/*.cpp
    lib/*.h
)

# Automatically gather test files
file(GLOB_RECURSE TEST_SOURCES
    tests/*.cpp
)

# Create a library for shared code
add_library(Lib ${APP_SOURCES})

# Include directories for the shared library
target_include_directories(Lib PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Create the application target
add_executable(App src/main.cpp)

# Link the shared library with the application
target_link_libraries(App PRIVATE Lib)

# Create the test target
add_executable(Tests ${TEST_SOURCES})

# Include directories for the tests
target_include_directories(Tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link GoogleTest and the shared library with the test executable
target_link_libraries(Tests PRIVATE gtest gtest_main Lib)

# Ensure both executables use C++17
set_target_properties(App Tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)

# Add tests to CTest
add_test(NAME TestSuite COMMAND Tests)
