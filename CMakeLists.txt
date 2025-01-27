cmake_minimum_required(VERSION 3.10)
project(FyneServer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HEADER_DIR "${CMAKE_SOURCE_DIR}/libs")
add_executable(FyneServer
  src/main.cxx
  src/entry.cxx
  src/udp.cxx
  src/packet.cxx
)

target_compile_definitions(FyneServer PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
target_include_directories(FyneServer PRIVATE ${HEADER_DIR})
