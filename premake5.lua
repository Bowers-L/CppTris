workspace "CppTris"
	architecture "x64"

	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "CppTris_Game"
	location "CppTris_Game"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/Assets/Shaders/**.shader"
	}

	includedirs {
		"%{prj.name}/vendor/glad/include",
		"%{prj.name}/vendor/glm-master",
		"%{prj.name}/vendor/SDL2-2.24.0/include",
		"%{prj.name}/vendor/SDL2_image-2.6.2/include",
		"%{prj.name}/src"
	}

	links {
		"SDL2",
		"SDL2main",
		"SDL2_Image"
	}

	libdirs {
		"%{prj.name}/vendor/SDL2-2.24.0/lib",
		"%{prj.name}/vendor/SDL2_image-2.6.2/lib"
	}

	postbuildcommands {
		("{COPY} vendor/SDL2-2.24.0/lib/SDL2.dll ../bin/" .. outputdir .. "/CppTris_Game"),
		("{COPY} vendor/SDL2_image-2.6.2/lib/SDL2_Image.dll ../bin/" .. outputdir .. "/CppTris_Game"),
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"