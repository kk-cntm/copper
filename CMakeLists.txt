cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_TYPES "Debug" "Release" "Dist")
set(CMAKE_CONFIGURATION_TYPES "${BUILD_TYPES}" CACHE STRING "list of supported configuration types" FORCE)

project(CopperRoot)

add_subdirectory(Copper)
add_subdirectory(Sandbox)
