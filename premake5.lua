workspace "SoftRender"
    configurations {"Debug", "Release"}

project "SoftRender"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    
    includedirs { "Source/**", "../SDL2-2.0.5/include"}
    libdirs {"../SDL2-2.0.5/lib/x64"}
    links {"SDL2.lib"}

    files { "Source/**.h", "Source/**.cpp"}

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "on"
      architecture "x86_64"
      targetdir "Binaries/Debug"
      objdir "Intermediate/Debug"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      architecture "x86_64"
      targetdir "Binaries/Release"
      objdir "Intermediate/Release"
