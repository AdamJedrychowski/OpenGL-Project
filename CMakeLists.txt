cmake_minimum_required(VERSION 3.13)
project(simple_example)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

add_subdirectory(Breakout)
add_subdirectory(ImGui-SFML)