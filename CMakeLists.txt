# Minimum version of CMake required to build this project
cmake_minimum_required( VERSION 3.22.1 )

# Name of project
project( Parser LANGUAGES CXX C )

# CMake standard (C++11)
set( CMAKE_CXX_STANDARD 11 )

# Retrieve googletest package
include( FetchContent )
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)

FetchContent_MakeAvailable( googletest )

# Enable googletest
enable_testing()

# Add path to all dependency directories
include_directories(
    include
    src
    test
)

# Add all the source files needed to build executable
add_library( TlmParser STATIC src/tlm_parser.cpp )

add_executable( TlmParserTests test/TlmParserTests.cpp )

target_link_libraries(
    TlmParserTests
    gtest_main
)

include( GoogleTest )
gtest_discover_tests( TlmParserTests )