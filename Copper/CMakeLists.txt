cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(Copper)

set(IMGUI_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_truetype.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_textedit.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imstb_rectpack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imconfig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp)

set(STB_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/stb_image.h
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image/stb_image.cpp)

set(GLAD_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c)

file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${STB_SRC})
add_library(Glad ${GLAD_SRC})
add_library(ImGui ${IMGUI_SRC})

target_link_libraries(${PROJECT_NAME}
        glfw
        glm
        Glad
        ImGui)

if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    find_library(CORE_FOUNDATION_LIB CoreFoundation)
    find_library(IO_KIT_LIB IOKit)
    find_library(COCOA_LIB Cocoa)
    find_library(OPENGL_LIB OpenGL)

    target_link_libraries(${PROJECT_NAME}
            ${CORE_FOUNDATION_LIB}
            ${IO_KIT_LIB}
            ${COCOA_LIB}
            ${OPENGL_LIB})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW)

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fvisibility=hidden")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-force_load libImGui.a ")

target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC" "-g")

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/cprpch.h)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_DEBUG CPR_ENABLE_ASSERTS)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_RELEASE)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_DIST)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_PLATFORM_MACOS)
    message(DEBUG "MACOS platform")
else()
    message(FATAL_ERROR "Not supported OS")
endif()
