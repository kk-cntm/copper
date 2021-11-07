workspace "Copper"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Copper"
    location "Copper"
    language "C++"
    cppdialect "C++17"
    kind "StaticLib"
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
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:macosx"
        systemversion "latest"

        xcodebuildsettings
        {
            ["ALWAYS_SEARCH_USER_PATHS"] = "YES"
        }

        defines
        {
            "CPR_PLATFORM_MACOS"
        }

    filter "configurations:Debug"
        defines "CPR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CPR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CPR_DIST"
        optimize "On"

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
        "Copper/vendor/spdlog/include"
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
    
    filter "configurations:Debug"
        defines "CPR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CPR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CPR_DIST"
        optimize "On"
        
