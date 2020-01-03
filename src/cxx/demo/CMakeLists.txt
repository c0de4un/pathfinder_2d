# // ------------------------------------------------------------------------------
# 
# This is CMake-File for PathFinder2D executable demo.
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
set ( PROJECT_NAME "Pathfinder2DDemo" )

# Project Version
set ( PROJECT_VERSION 1.1.2 )

# Configure Project
project ( ${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C CXX )

# C Version
#set ( CMAKE_C_STANDARD 99 )

# C++ Version
#set ( CMAKE_CXX_STANDARD 11 )

# Make Build Libs & Executables to be position-independent, like SHARED libs.
#set ( CMAKE_POSITION_INDEPENDENT_CODE ON )

# =================================================================================
# CONSTANTS
# =================================================================================

# Set Sources Dir
#set ( SOURCES_DIR "${CMAKE_SOURCE_DIR}/src/cxx" PARENT_SCOPE )

# Set Project Bin-Output Dir
#set ( ROOT_PROJECT_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${BUILD_TYPE_DIR}/${PLATFORM_DIR}" PARENT_SCOPE )

# =================================================================================
# HEADERS
# =================================================================================

# Headers
set ( PROJECT_HEADERS "${SOURCES_DIR}/main.hpp"
    # UTILS
    "${SOURCES_DIR}/demo/IConsoleOutput.hpp"
    # DEMO
    "${SOURCES_DIR}/demo/IMapFactory.hxx"
    "${SOURCES_DIR}/demo/MapDemo.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

# Sources
set ( PROJECT_SOURCES "${SOURCES_DIR}/main.cpp"
    # UTILS
    "${SOURCES_DIR}/demo/IConsoleOutput.cpp"
    # DEMO
    "${SOURCES_DIR}/demo/IMapFactory.cpp"
    "${SOURCES_DIR}/demo/MapDemo.cpp" )

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
	message ( SEND_ERROR "${PROJECT_NAME} - executable resources configuration required !" )
endif ( WIN32 OR WIN64 ) # Windows

# =================================================================================
# BUILD EXECUTABLE
# =================================================================================

# PLATFORM
if ( WIN32 OR WIN64 ) # Windows

    # Create Executable Object
    add_executable ( pathfinder_2d_demo ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${ROOT_PROJECT_RESOURCES} )

    # Connecting the library, specify where to get the header files
    include_directories ( "../pathfinder2d" )

    # Link Executable with Libraries
    target_link_libraries ( pathfinder_2d_demo Pathfinder2DLibCore )

    # Configure Executable Object
    set_target_properties ( pathfinder_2d_demo PROPERTIES
    OUTPUT_NAME "pathfinder_2d_demo"
    RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

elseif ( LINUX ) # Linux

    # Create Executable Object
    add_executable ( pathfinder_2d ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )

    # Connecting the library, specify where to get the header files
    include_directories ( "../pathfinder2d" )

    # Link Executable with Libraries
    target_link_directories ( ${pathfinder_2d} Pathfinder2DLibCore )

    # Configure Executable Object
    set_target_properties ( pathfinder_2d PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

elseif ( MAC ) # Mac

    # Create Executable Object
    add_executable ( pathfinder_2d ${ROOT_PROJECT_SOURCES} ${ROOT_PROJECT_HEADERS} ${ROOT_PROJECT_RESOURCES} )

    # Connecting the library, specify where to get the header files
    include_directories ( "../pathfinder2d" )

    # Link Executable with Libraries
    target_link_directories ( ${pathfinder_2d} Pathfinder2DLibCore )
    
    # Configure Executable Object
    set_target_properties ( pathfinder_2d PROPERTIES
    OUTPUT_NAME "${PROJECT_NAME}"
    RUNTIME_OUTPUT_DIRECTORY ${ROOT_PROJECT_OUTPUT_DIR} )

else ( WIN32 OR WIN64 )
    # ERROR
    message ( FATAL_ERROR "${PROJECT_NAME} - can't build executable for current platform, configuration rquired." )
endif ( WIN32 OR WIN64 ) # Windows

# INFO
message ( STATUS "${PROJECT_NAME} - Executable saved at ${ROOT_PROJECT_OUTPUT_DIR}" )