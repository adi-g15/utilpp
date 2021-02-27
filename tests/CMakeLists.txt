cmake_minimum_required(VERSION 3.16)
project(utilpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# setting location of executable to be same as build directory for same location of executable wither on windows or linux
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
file(GLOB TEST_SOURCES file_test.cpp string_test.cpp)
add_executable(tests tests.cpp ${TEST_SOURCES})

target_include_directories(tests PRIVATE ../includes)
