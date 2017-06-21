project "RavenScript"
	kind "ConsoleApp"
	language "C++"
	location "vs2013"
	debugdir ".."

	files { "../source/**.hpp", "../source/**.h", "../source/**.cpp" }
	includedirs
	{
		"../source"
	}
	flags { "WinMain" }

	configuration "Debug"
		defines { "WIN32", "_DEBUG", "DEBUG", "PROFILE", "_WINDOWS" }
		targetdir "../bin"
		targetname "RavenScript_d"
		symbols "on"

	configuration "Release"
		defines { "WIN32", "NDEBUG", "_WINDOWS" }
		targetdir "../bin"
		targetname "RavenScript"
