workspace "steering-behavior"
    location "build"
    architecture "x64"
    configurations { "Debug", "Release" }

    kind "ConsoleApp"
    language "C++"
    
project "steering-behavior"  
    location "build"

    defines "SFML_STATIC"
    files {
        "src/**.cpp",
        "src/**.hpp",
        "libraries/include/ImGui/**.cpp",
        "libraries/include/ImGui/**.h"
    }
  
    includedirs  { "libraries/*", "src" }
    libdirs "libraries/lib"
    links {
        "opengl32",
        "winmm",
    }

    filter "configurations:Debug"
    defines "DEBUG"
    symbols "On"
    links {
        "sfml-system-s-d",
        "sfml-window-s-d",
        "sfml-graphics-s-d"
    }

    filter "configurations:Release"
    defines "RELEASE"
    optimize "Speed"
    links {
        "sfml-system-s",
        "sfml-window-s",           
        "sfml-graphics-s"         
    }