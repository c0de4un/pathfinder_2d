# // ------------------------------------------------------------------------------
# 
# This is root CMake-File for PathFinder2D example-project.
# 
# About:
# Pathfinder2D - demonstrates on how to use 'wave' || 'BFS' || ('Width')
# based search rules. Main goal/task of method if to find shortest (fastest)
# route/path to a destinations, if map known.
# 
# License: see "LICENSE" file.
# Tools: Visual Studio Code (VSCode), Ninja, CMake, MSBuild (MSVC).
# API: C++ 11 is minimum.
# Platforms: Any with C++ 11 support.
# 
# // ------------------------------------------------------------------------------

# =================================================================================
# CMake Meta-Data
# =================================================================================

# CMake-Version
cmake_minimum_required ( VERSION 3.6 FATAL_ERROR )

# =================================================================================
# PROJECT
# =================================================================================

# Project Name
set ( ROOT_PROJECT_NAME "Pathfinder2D" )

# Project Version
set ( ROOT_PROJECT_VERSION 1.1.2 )

# Configure Project
project ( ${ROOT_PROJECT_NAME} VERSION ${ROOT_PROJECT_VERSION} LANGUAGES C CXX )

# C Version
#set ( CMAKE_C_STANDARD 99 )

# C++ Version
#set ( CMAKE_CXX_STANDARD 11 )

# Make Build Libs & Executables to be position-independent, like SHARED libs.
#set ( CMAKE_POSITION_INDEPENDENT_CODE ON )

# =================================================================================
# CONFIG
# =================================================================================

# DETECT LINUX
if ( NOT ANDROID AND UNIX AND NOT DEFINED LINUX AND NOT APPLE )
		
	# LINUX ON
	set ( LINUX ON )
	
endif ( NOT ANDROID AND UNIX AND NOT DEFINED LINUX AND NOT APPLE )

# PLATFORM
if ( ANDROID ) # ANDROID

	# Set Directory Prefix
	set ( PLATFORM_DIR "android" )
	
elseif ( WIN32 ) # WINDOWS

	# Set Directory Prefix
    set ( PLATFORM_DIR "win32" )
    add_definitions( -DWINDOWS=1 )
elseif ( WIN64 ) # WINDOWS x64

	# Set Directory Prefix
    set ( PLATFORM_DIR "win64" )
    add_definitions( -DWINDOWS=1 )
elseif ( LINUX ) # LINUX
	
	# Set Directory Prefix
	set ( PLATFORM_DIR "linux" )
    add_definitions( -DLINUX=1 )
elseif ( APPLE ) # APPLE

	# Set Directory Prefix
    set ( PLATFORM_DIR "apple" )
    add_definitions( -DAPPLE=1 )
else ( ANDROID ) # ?
	
	# ERROR
	message ( SEND_ERROR "${ROOT_PROJECT_NAME} - unknown platform ! Configuration required." )
	
	# Set Directory Prefix
	set ( PLATFORM_DIR "unix" )
	
endif ( ANDROID )

# Build-Type Sub-Dir
if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

	# Add Definition
	add_definitions ( -DDEBUG=1 )
	
	# Set Build-Type Dir
	set ( BUILD_TYPE_DIR "debug" )
	
else ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

	# Set Build-Type Dir
	set ( BUILD_TYPE_DIR "release" )
	
endif ( CMAKE_BUILD_TYPE STREQUAL "Debug" )

# =================================================================================
# CONSTANTS
# =================================================================================

# Asset File
add_definitions ( -DMAP_DEMO_FILE="${CMAKE_SOURCE_DIR}/assets/tiles_map.txt" )

# Set Sources Dir
set ( SOURCES_DIR "${CMAKE_SOURCE_DIR}/src/cxx" )

# Set Project Bin-Output Dir
set ( ROOT_PROJECT_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${BUILD_TYPE_DIR}/${PLATFORM_DIR}" )

# =================================================================================
# HEADERS
# =================================================================================

# Headers
# set ( ROOT_PROJECT_HEADERS "${SOURCES_DIR}/main.hpp"
#     # UTILS
#     "${SOURCES_DIR}/demo/IConsoleOutput.hpp"
#     # TILES
#     "${SOURCES_DIR}/pathfinder2d/cfg/pathfinder2d.hpp"
#     "${SOURCES_DIR}/pathfinder2d/core/IMap2DEventsHandler.hxx"
#     "${SOURCES_DIR}/pathfinder2d/core/Map2D.hpp"
#     # DEMO
#     "${SOURCES_DIR}/demo/MapDemo.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

# Sources
# set ( ROOT_PROJECT_SOURCES "${SOURCES_DIR}/main.cpp"
#     # UTILS
#     "${SOURCES_DIR}/demo/IConsoleOutput.cpp"
#     # TILES
#     "${SOURCES_DIR}/pathfinder2d/core/Map2D.cpp"
#     # DEMO
#     "${SOURCES_DIR}/demo/MapDemo.cpp" )

# =================================================================================
# PRECOMPILED HEADERS
# =================================================================================

# =================================================================================
# MODULES
# =================================================================================

# PathFinder2D.Lib.Core
add_subdirectory ( "src/cxx/pathfinder2d" )

# PathFinder2D.Demo
add_subdirectory ( "src/cxx/demo" )

# =================================================================================
# EXECUTABLE RESOURCES
# =================================================================================

# PLATFORM
# if ( WIN32 OR WIN64 ) # Windows
#     set ( ROOT_PROJECT_RESOURCES "${CMAKE_SOURCE_DIR}/res/win32_resources.rc" )
# elseif ( LINUX ) # Linux
#     set ( ROOT_PROJECT_RESOURCES "" )
# elseif ( MAC ) # Mac
#     set ( ROOT_PROJECT_RESOURCES "" )
# else ( WIN32 OR WIN64 ) # Unknown
# 	message ( SEND_ERROR "${ROOT_PROJECT_NAME} - executable resources configuration required !" )
# endif ( WIN32 OR WIN64 ) # Windows

# =================================================================================
# BUILD EXECUTABLE
# =================================================================================

# PLATFORM
# if ( WIN32 OR WIN64 ) # Windows

#     # Create Executable Object
#     add_executable ( pathfinder_2d ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )

#     # Configure Executable Object
#     set_target_properties ( pathfinder_2d PROPERTIES
#     OUTPUT_NAME "${ROOT_PROJECT_NAME}"
#     RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

# elseif ( LINUX ) # Linux

#     # Create Executable Object
#     add_executable ( pathfinder_2d ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )

#     # Configure Executable Object
#     set_target_properties ( pathfinder_2d PROPERTIES
#     OUTPUT_NAME "${ROOT_PROJECT_NAME}"
#     RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

# elseif ( MAC ) # Mac

#     # Create Executable Object
#     add_executable ( pathfinder_2d ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )

#     # Configure Executable Object
#     set_target_properties ( pathfinder_2d PROPERTIES
#     OUTPUT_NAME "${ROOT_PROJECT_NAME}"
#     RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

# else ( WIN32 OR WIN64 )
#     # ERROR
#     message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - can't build executable for current platform, configuration rquired." )
# endif ( WIN32 OR WIN64 ) # Windows