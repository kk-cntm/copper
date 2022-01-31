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

group "dependencies"
    include "Copper/vendor/GLFW"
    include "Copper/vendor/glad"
    include "Copper/vendor/imgui"
group ""

include "Copper"
include "Sandbox"