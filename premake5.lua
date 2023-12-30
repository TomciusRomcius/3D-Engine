workspace "3D-Engine"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}

    project "Engine"
        kind "SharedLib"
        location "Engine"
        language "c++"

        outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/".. outputdir .."/%{prj.name}")

        pchheader "enpch.h"
        pchsource "%{prj.name}/src/enpch.cpp"

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
        includedirs
        {
            "vendor/glfw/include",
            "vendor/glew/include",
            "vendor/glm-master",
            "vendor/spdlog/include",
            "vendor/stb/include",
            "%{prj.name}/src/"
        }

        libdirs
        {
            "vendor/glfw/lib",
            "vendor/glew/lib/Release/x64"
        }

        links
        {
            "opengl32.lib",
            "glew32s.lib",
            "glfw3.lib"
        }
        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
        filter "configurations:Debug"
            defines {"DEBUG", "EN_BUILD_DLL", "GLEW_STATIC"}
            symbols "On"
        filter "configurations:Release"
            defines {"NDEBUG", "EN_BUILD_DLL", "GLEW_STATIC"}
            optimize "On"
        filter "configurations:Dist"
            defines {"NDEBUG", "Dist", "EN_BUILD_DLL", "GLEW_STATIC"}
            optimize "On"

    project "Sandbox"
        kind "ConsoleApp"
        location "Sandbox"
        language "c++"

        outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/".. outputdir .."/%{prj.name}")


        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
        includedirs
        {
            "vendor/glfw/include",
            "vendor/glew/include",
            "vendor/glm-master",
            "vendor/spdlog/include",
            "vendor/stb/include",
            "Engine/src"
        }

        libdirs
        {
            "vendor/glfw/lib",
            "vendor/glew/lib/Release/x64"
        }

        links
        {
            "Engine",
            "opengl32.lib",
            "glew32s.lib",
            "glfw3.lib"
        }
        filter "configurations:Debug"
            defines {"DEBUG", "EN_BUILD_DLL", "GLEW_STATIC"}
            symbols "On"
        filter "configurations:Release"
            defines {"NDEBUG", "EN_BUILD_DLL", "GLEW_STATIC"}
            optimize "On"
        filter "configurations:Dist"
            defines {"NDEBUG", "Dist", "EN_BUILD_DLL", "GLEW_STATIC"}
            optimize "On"





