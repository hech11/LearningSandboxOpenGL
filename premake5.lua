workspace "LearningSandboxOpenGL"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "LearningOpenGL-Core/vendor/GLFW"

group "Dependencies"
	include "LearningOpenGL-Core/vendor/GLFW"
group ""


project "LearningOpenGL-Core"
	location "LearningOpenGL-Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "LearningOpenGL-Core/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor"

	}

	links
	{
		"GLFW"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"GLFW_INCLUDE_NONE",
			"LSO_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LSO_DEBUG"
		runtime "Debug"
		symbols "on"



	filter "configurations:Release"
		defines "LSO_RELEASE"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"LearningOpenGL-Core/src",
		"LearningOpenGL-Core/vendor",
	}

	links
	{
		"GLFW",
		"LearningOpenGL-Core"
	}



	filter "system:windows"
		systemversion "latest"


		defines
		{
			"GLFW_INCLUDE_NONE",
			"LSO_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "LSO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LSO_RELEASE"
		runtime "Release"
		optimize "on"
