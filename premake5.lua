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
		"%{prj.name}/src/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
	}


	filter "system:windows"
		systemversion "latest"

		defines
		{
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
	}

	links
	{
		"LearningOpenGL-Core"
	}



	filter "system:windows"
		systemversion "latest"


		defines
		{
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
