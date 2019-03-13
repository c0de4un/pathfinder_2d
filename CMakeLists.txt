# // ------------------------------------------------------------------------------ \\
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
# // ------------------------------------------------------------------------------ \\

# =================================================================================
# CMake Meta-Data
# =================================================================================

# CMake-Version
cmake_minimum_required ( VERSION 3.8 FATAL_ERROR )

# =================================================================================
# PROJECT
# =================================================================================

# Project Name
set ( ROOT_PROJECT_NAME "Pathfinder2D" )

# Project Version
set ( ROOT_PROJECT_VERSION 1.0.0 )

# Configure Project
project ( ${ROOT_PROJECT_NAME} VERSION ${ROOT_PROJECT_VERSION} LANGUAGES C CXX )

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

elseif ( WIN64 ) # WINDOWS x64

	# Set Directory Prefix
	set ( PLATFORM_DIR "win64" )

elseif ( LINUX ) # LINUX
	
	# Set Directory Prefix
	set ( PLATFORM_DIR "linux" )

elseif ( APPLE ) # APPLE

	# Set Directory Prefix
	set ( PLATFORM_DIR "apple" )

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

# Set Sources Dir
set ( SOURCES_DIR "${CMAKE_SOURCE_DIR}/src/cpp" )

# Set Project Bin-Output Dir
set ( ROOT_PROJECT_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${BUILD_TYPE_DIR}/${PLATFORM_DIR}" )

# =================================================================================
# HEADERS
# =================================================================================

# Headers
set ( ROOT_PROJECT_HEADERS "${SOURCES_DIR}/main.hpp"
"${SOURCES_DIR}/pch_cxx.hpp"
"${SOURCES_DIR}/tiles/tiles_fwd.hpp"
"${SOURCES_DIR}/tiles/Tile.hpp"
"${SOURCES_DIR}/tiles/Route.hpp"
"${SOURCES_DIR}/tiles/TMap.hpp"
"${SOURCES_DIR}/tiles/TilesManager.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

# Sources
set ( ROOT_PROJECT_SOURCES "${SOURCES_DIR}/main.cpp"
"${SOURCES_DIR}/pch_cxx.cpp"
"${SOURCES_DIR}/tiles/TilesManager.cpp" )

# =================================================================================
# PRECOMPILED HEADERS
# =================================================================================

# =================================================================================
# EXECUTABLE RESOURCES
# =================================================================================

# PLATFORM
if ( WIN32 OR WIN64 ) # Windows
    set ( ROOT_PROJECT_RESOURCES "${CMAKE_SOURCE_DIR}/res/win32_resources.rc" )
elseif ( LINUX ) # Linux
    set ( ROOT_PROJECT_RESOURCES "" )
elseif ( MAC ) # Mac
    set ( ROOT_PROJECT_RESOURCES "" )
else ( WIN32 OR WIN64 ) # Unknown
	message ( SEND_ERROR "${ROOT_PROJECT_NAME} - executable resources configuration required !" )
endif ( WIN32 OR WIN64 ) # Windows

# =================================================================================
# BUILD EXECUTABLE
# =================================================================================

# PLATFORM
if ( WIN32 OR WIN64 ) # Windows

    # Create Executable Object
    add_executable ( pathfinder_2d ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )

    # Configure Executable Object
    set_target_properties ( pathfinder_2d PROPERTIES
    OUTPUT_NAME "${ROOT_PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

elseif ( LINUX ) # Linux

    # Create Executable Object
    add_executable ( pathfinder_2d ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )

    # Configure Executable Object
    set_target_properties ( pathfinder_2d PROPERTIES
    OUTPUT_NAME "${ROOT_PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

elseif ( MAC ) # Mac

    # Create Executable Object
    add_executable ( pathfinder_2d ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )

    # Configure Executable Object
    set_target_properties ( pathfinder_2d PROPERTIES
    OUTPUT_NAME "${ROOT_PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

else ( WIN32 OR WIN64 )
    # ERROR
    message ( FATAL_ERROR "${ROOT_PROJECT_NAME} - can't build executable for current platform, configuration rquired." )
endif ( WIN32 OR WIN64 ) # Windows