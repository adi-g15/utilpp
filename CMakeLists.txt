cmake_minimum_required(VERSION 3.14)

project(utilpp)

# specify this library not meant to generate any build output
add_library(utilpp INTERFACE)
target_include_directories(utilpp INTERFACE include/)

install(DIRECTORY include/util
        TYPE INCLUDE)
