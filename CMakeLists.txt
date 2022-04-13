cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(CopperRoot)

set(BUILD_TYPES "Debug" "Release" "Dist")
set(CMAKE_CONFIGURATION_TYPES "${BUILD_TYPES}" CACHE STRING "list of supported configuration types" FORCE)

if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    set(CPR_PLATFORM MacOS)
    set(CPR_AVAILABLE_GRAPHIC_APIS OpenGL)
else ()
    message(FATAL_ERROR "Not supported OS")
endif ()

add_subdirectory(Copper)
add_subdirectory(Sandbox)
