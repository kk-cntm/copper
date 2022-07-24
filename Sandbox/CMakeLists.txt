cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(Sandbox)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Sandbox.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Sandbox.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Sandbox2D.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Sandbox2D.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_DEBUG CPR_ENABLE_ASSERTS CPR_ENABLE_PROFILER)
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_RELEASE CPR_ENABLE_PROFILER)
elseif (CMAKE_BUILD_TYPE STREQUAL Dist)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_DIST)
endif ()

if (CPR_PLATFORM STREQUAL MacOS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_PLATFORM_MACOS)
else ()
    message(FATAL_ERROR "Not supported OS")
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/vendor/spdlog/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/vendor/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/vendor/glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/vendor)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Copper/src)
target_include_directories(${PROJECT_NAME} PRIVATE src)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets)

add_dependencies(${PROJECT_NAME} Copper)

target_link_libraries(${PROJECT_NAME} Copper)