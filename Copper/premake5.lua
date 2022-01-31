project "Copper"
    language "C++"
    cppdialect "C++17"
    kind "SharedLib"
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "cprpch.h"
    pchsource "src/cprpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/imgui/backends/imgui_impl_opengl3.cpp",
        "vendor/imgui/backends/imgui_impl_opengl3.h",
        "vendor/imgui/backends/imgui_impl_glfw.cpp",
        "vendor/imgui/backends/imgui_impl_glfw.h",
        "vendor/stb_image/stb_image.h",
        "vendor/stb_image/stb_image.cpp"
    }

    includedirs
    {
        "src",
        "vendor/spdlog/include",
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
