cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(CopperCore)

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

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/OrthoCameraController.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/OrthoCameraController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Core.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/EntryPoint.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/ImGuiHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Input.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/KeyCodes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/LayerStack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/LayerStack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Log.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Log.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/MouseCodes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Platform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Timestep.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/hash.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/hash.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/siphash.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Core/siphash.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Event/ApplicationEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Event/Event.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Event/KeyEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Event/MouseEvent.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Buffer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/GraphicContext.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/OrthoCamera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/OrthoCamera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/RenderCommand.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/RenderCommand.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Renderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Renderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/RendererAPI.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/ShaderData.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/ShaderData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/VertexArray.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Renderer2D.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Renderer/Renderer2D.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/BundleSerializer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/BundleSerializer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/BundleDeserializer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/BundleDeserializer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/FileMime.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/FileMime.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/Rms.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/Rms.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/Resource.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/Resource.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/context.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/bundle-sections/versionsection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/bundle-sections/versionsection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/bundle-sections/metatablesection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/bundle-sections/metatablesection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/bundle-sections/assetssection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Resource/bundle-sections/assetssection.cpp)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    list(APPEND SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Debug/DebugProfiler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Copper/Debug/DebugProfiler.cpp)
endif ()

if (CPR_PLATFORM STREQUAL MacOS)
    list(APPEND SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/MacOsImGuiHandler.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/MacOsImGuiHandler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/MacOsInput.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/MacOsInput.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/MacOsPlatform.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/MacOsPlatform.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/MacOsWindow.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/MacOsWindow.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/Renderer/MacOsBuffer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/Renderer/MacOsRenderCommand.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/Renderer/MacOsShader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/Renderer/MacOsTexture.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/MacOs/Renderer/MacOsVertexArray.cpp)
endif ()

if (OpenGL IN_LIST CPR_AVAILABLE_GRAPHIC_APIS)
    list(APPEND SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLBuffer.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLBuffer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLContext.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLContext.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLRendererAPI.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLRendererAPI.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLShader.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLShader.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLTexture.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLTexture.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLVertexArray.h
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Platform/OpenGL/OpenGLVertexArray.cpp)
else ()
    message(FATAL_ERROR "Unsupported graphic api")
endif ()

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${STB_SRC})
add_library(Glad ${GLAD_SRC})
add_library(ImGui ${IMGUI_SRC})

target_link_libraries(${PROJECT_NAME}
        glfw
        glm
        Glad
        ImGui
        pugixml
        zlib)

if (${CPR_PLATFORM} STREQUAL MacOS)
    find_library(CORE_FOUNDATION_LIB CoreFoundation)
    find_library(IO_KIT_LIB IOKit)
    find_library(COCOA_LIB Cocoa)
    find_library(OPENGL_LIB OpenGL)

    target_link_libraries(${PROJECT_NAME}
            ${CORE_FOUNDATION_LIB}
            ${IO_KIT_LIB}
            ${COCOA_LIB}
            ${OPENGL_LIB})
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb_image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/pugixml/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/zlib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/pugixml)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/zlib)

if (CPR_ENABLE_UNITTESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest)
    add_subdirectory(tests)
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fvisibility=hidden")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-force_load ${CMAKE_CURRENT_BINARY_DIR}/libImGui.a ")

target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC" "-g")

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/cprpch.h)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_DEBUG CPR_ENABLE_ASSERTS CPR_ENABLE_PROFILER)
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_RELEASE CPR_ENABLE_PROFILER)
elseif (CMAKE_BUILD_TYPE STREQUAL Dist)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_DIST)
endif ()

if (CPR_PLATFORM STREQUAL MacOS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPR_PLATFORM_MACOS)
    message(DEBUG "MACOS platform")
else ()
    message(FATAL_ERROR "Not supported OS")
endif ()
