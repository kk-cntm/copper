project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Copper/src",
        "%{wks.location}/Copper/vendor",
        "%{wks.location}/Copper/vendor/spdlog/include",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Copper"
    }

    filter "system:macosx"
        systemversion "11.0"

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
