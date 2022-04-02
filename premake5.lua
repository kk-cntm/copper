require "clion"

workspace "Copper"
    architecture "ARM64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Copper/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Copper/vendor/glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Copper/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Copper/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Copper/vendor/stb_image"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "dependencies"
    include "Copper/vendor/GLFW"
    include "Copper/vendor/glad"
    include "Copper/vendor/imgui"
group ""

include "Copper"
include "Sandbox"