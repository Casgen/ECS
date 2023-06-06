---@diagnostic disable: undefined-global
workspace "ECS"
  configurations {"Debug", "Release"}

project "OGLLibrary"
  kind "StaticLib"

  language "C++"
  cppdialect "C++20"

  location "%{prj.name}/build"
  targetdir "%{prj.name}/bin/%{cfg.buildcfg}"
  objdir "%{prj.name}/obj/%{cfg.buildcfg}"

  files {
    "%{prj.name}/Vendor/**",
    "%{prj.name}/Src/**.cpp",
    "%{prj.name}/Src/**.h",
    "%{prj.name}/Src/**.hpp",
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "on"

  includedirs {
    "%{prj.name}/Vendor",
  }

  filter { "system:linux" }
    links {"GL"}

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"

project "ECSImplementation"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  location "%{prj.name}/build"
  targetdir "%{prj.name}/bin/%{cfg.buildcfg}"
  objdir "%{prj.name}/obj/%{cfg.buildcfg}"

  links { "OGLLibrary" }

  includedirs {
    "%{prj.name}/Vendor", -- includes the directories as such (#include <glm/vec4.hpp>)
    "OGLLibrary/Vendor", -- includes the directories as such (#include <glm/vec4.hpp>)
    "OGLLibrary/Src"
  }

  files
  {
    "%{prj.name}/Src/**.h",
    "%{prj.name}/Src/**.cpp",
    "%{prj.name}/Src/**.hpp",
  }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "on"

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"

postbuildcommands {
  "bear -- make"
}
