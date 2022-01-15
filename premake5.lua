workspace "Copper"
    architecture "ARM64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

IncludeDir = {}
IncludeDir["GLFW"] = "Copper/vendor/GLFW/include"
IncludeDir["Glad"] = "Copper/vendor/glad/include"
IncludeDir["ImGui"] = "Copper/vendor/imgui"
IncludeDir["glm"] = "Copper/vendor/glm"
IncludeDir["stb_image"] = "Copper/vendor/stb_image"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Copper/vendor/GLFW"
include "Copper/vendor/glad"
include "Copper/vendor/imgui"

project "Copper"
    location "Copper"
    language "C++"
    cppdialect "C++17"
    kind "SharedLib"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "src/cprpch.h"
    pchsource "Copper/src/cprpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/imgui/backends/imgui_impl_opengl3.cpp",
        "%{prj.name}/vendor/imgui/backends/imgui_impl_opengl3.h",
        "%{prj.name}/vendor/imgui/backends/imgui_impl_glfw.cpp",
        "%{prj.name}/vendor/imgui/backends/imgui_impl_glfw.h",
        "%{prj.name}/vendor/stb_image/stb_image.h",
        "%{prj.name}/vendor/stb_image/stb_image.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui"
    }

    defines
    {
        -- make it possible to use glad with GLFW
        "GLFW_INCLUDE_NONE"
    }

    filter "system:macosx"
        systemversion "latest"

        xcodebuildsettings
        {
            ["ALWAYS_SEARCH_USER_PATHS"] = "YES"
        }

        links
        {
            "CoreFoundation.framework",
            "IOKit.framework",
            "Cocoa.framework",
            "OpenGL.framework"
        }

        defines
        {
            "CPR_PLATFORM_MACOS"
        }

    filter "toolset:clang"
        linkoptions
        {
            -- expose imgui core interface
            "-force_load %{prj.location}/vendor/imgui/bin/" .. outputdir .. "/ImGui/libImGui.a"
        }

        buildoptions
        {
            "-fvisibility=hidden"
        }

    filter "configurations:Debug"
        defines
        {
            "CPR_DEBUG",
            "CPR_ENABLE_ASSERTS"
        }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines "CPR_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "CPR_DIST"
        optimize "On"
        runtime "Release"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Copper/src",
        "Copper/vendor",
        "Copper/vendor/spdlog/include",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Copper"
    }

    filter "system:macosx"
        systemversion "latest"

        xcodebuildsettings
        {
            ["ALWAYS_SEARCH_USER_PATHS"] = "YES"
        }

        postbuildcommands
        {
            -- copy assets dir to build directory
            "cp -rf %{prj.location}/assets %{cfg.buildtarget.directory}"
        }

    filter "configurations:Debug"
        defines
        {
            "CPR_DEBUG",
            "CPR_ENABLE_ASSERTS"
        }
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        defines "CPR_RELEASE"
        optimize "On"
        runtime "Release"

    filter "configurations:Dist"
        defines "CPR_DIST"
        optimize "On"
        runtime "Release"
