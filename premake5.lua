---@diagnostic disable: undefined-global
workspace "ECS"
  configurations {"Debug", "Release"}

  include "OGLLibrary/Vendor/glfw.lua"
  include "OGLLibrary/Vendor/glad.lua"
  include "OGLLibrary/Vendor/glm.lua"
  include "OGLLibrary/Vendor/imgui.lua"

  project "OGLLibrary"
    kind "StaticLib"

    language "C++"
    cppdialect "C++20"

    location "%{prj.name}/build"
    targetdir "%{prj.name}/bin/%{cfg.buildcfg}"
    objdir "%{prj.name}/obj/%{cfg.buildcfg}"


    links { "GLFW", "GLM", "GLAD", "ImGui" }

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "on"

    includedirs {
      "%{prj.name}/Vendor/glad/include", -- files are included like this <glad/glad.h>
      "%{prj.name}/Vendor/glfw/include/",
      "%{prj.name}/Vendor/glm/",
      "%{prj.name}/Vendor/imgui/",
      "%{prj.name}/Vendor/imgui/examples",
      "%{prj.name}/Vendor/stb_image"
    }

    files {
      "%{prj.name}/Src/**.cpp",
      "%{prj.name}/Src/**.h",
      "%{prj.name}/Src/**.hpp",
    }

    filter { "system:linux" }
      links { "dl", "pthread" }

      defines { "_X11" }

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

    links { "OGLLibrary", "GLFW", "GLM", "GLAD", "ImGui" }

    files
    {
      "%{prj.name}/Src/**.h",
      "%{prj.name}/Src/**.cpp",
      "%{prj.name}/Src/**.hpp",
    }

    includedirs {
      "OGLLibrary/Src",
      "OGLLibrary/Vendor/glad/include/", -- files are included like this <glad/glad.h>
      "OGLLibrary/Vendor/glfw/include/",
      "OGLLibrary/Vendor/glm/",
      "OGLLibrary/Vendor/imgui/",
    }


    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "on"

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
