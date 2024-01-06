workspace "3D-Engine"
    architecture "x64"
    configurations {"EngineDebug", "EngineRelease", "EngineDist, GameDebug, GameRelease, GameDist"}
    
    project "Engine"
        kind "ConsoleApp"
        location "Engine"
        language "c++"


        outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

        targetdir ("bin/" .. outputdir)
        objdir ("bin-int/".. outputdir)

        pchheader "enpch.h"
        pchsource "%{prj.name}/src/enpch.cpp"

        files
        {
            "%{prj.name}/src",
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }
        includedirs
        {
            "vendor/glfw/include",
            "vendor/glew/include",
            "vendor/glm-master",
            "vendor/spdlog/include",
            "vendor/stb/include",
            "imgui",
            "%{prj.name}/src/"
        }

        libdirs
        {
            "vendor/glfw/lib",
            "vendor/glew/lib/Release/x64"
        }

        links
        {
            "imgui",
            "opengl32.lib",
            "glew32s.lib",
            "glfw3.lib"
        }
        filter "configurations:EngineDebug"
            defines {"ENGINE_DEBUG", "EN_BUILD_DLL", "GLEW_STATIC"}
            symbols "On"
        filter "configurations:EngineRelease"
            defines {"NDEBUG", "EN_BUILD_DLL", "GLEW_STATIC"}
            optimize "On"
        filter "configurations:EngineDist"
            defines {"NDEBUG", "Dist", "EN_BUILD_DLL", "GLEW_STATIC"}
            optimize "On"
        filter "configurations:GameDebug"
            defines {"GAME_DEBUG", "EN_BUILD_DLL", "GLEW_STATIC"}
            symbols "On"
        filter "configurations:GameRelease"
            defines {"NDEBUG", "EN_BUILD_DLL", "GLEW_STATIC"}
            optimize "On"
        filter "configurations:GameDist"
            defines {"NDEBUG", "Dist", "EN_BUILD_DLL", "GLEW_STATIC"}
            optimize "On"

        targetDirectory = "bin/" .. outputdir .. "/Shaders"
        postbuildcommands
        {
            ("{COPY} %{prj.name}/Shaders %{targetDirectory}")
        }

    project "imgui"
        kind "SharedLib"
        location "imgui"
        language "c++"

        outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

        includedirs
        {
            "%{prj.name}",
            "vendor/glfw/include",
            "vendor/glew/include"
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

        targetdir ("bin/" .. outputdir)
        objdir ("bin-int/".. outputdir)

        files {
            "%{prj.name}/**.h",
            "%{prj.name}/**.cpp",
        }