cmake_minimum_required(VERSION 3.28.3)

# Your project settings
project(MyProject)

# Specify C++ standard (if required)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1  # Latest stable release as of Oct 2024
)
# Download and configure GoogleTest
FetchContent_MakeAvailable(googletest)

# Link GoogleTest to your project (for testing)
enable_testing()

# Automatically gather source files
file(GLOB_RECURSE SOURCES
    src/*.cpp  # All .cpp files in src directory and subdirectories
    src/*.h    # All .h files in src directory and subdirectories
)

# Automatically gather test files
file(GLOB_RECURSE TEST_SOURCES
    tests/*.cpp  # All .cpp files in tests directory and subdirectories
)

# Add your test files
add_executable(ProjectTests ${SOURCES} ${TEST_SOURCES})

# Include the src/ directory where add.h is located
target_include_directories(ProjectTests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link GoogleTest with your test executable
target_link_libraries(ProjectTests gtest gtest_main)

# Add tests to CTest
add_test(NAME MyTestSuite COMMAND ProjectTests)
