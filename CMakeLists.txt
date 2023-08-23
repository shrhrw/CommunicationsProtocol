# Minimum version of CMake required to build this project
cmake_minimum_required( VERSION 3.16.3 )

# Name of project
project( TlmParser LANGUAGES CXX C )

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
add_library( Iface STATIC src/iface.cpp )
add_library( TlmParser STATIC src/tlm_parser.cpp )

add_executable( TlmParserTests test/TlmParserTests.cpp )

target_link_libraries(
    TlmParserTests
    TlmParser   
    Iface
    gtest_main
)

include( GoogleTest )
gtest_discover_tests( TlmParserTests )
