workspace "RavenScript"
	configurations { "Debug", "Release" }
	platforms { "Win32", "x64" }

solution "RavenScript"
	location "../.."

	include "../../prj/premake5.lua"
