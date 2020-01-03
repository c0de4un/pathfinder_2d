# // ------------------------------------------------------------------------------
# 
# This is CMake-File for PathFinder2D lib.
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
set ( PROJECT_NAME "Pathfinder2DLibCore" )

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
# HEADERS
# =================================================================================

# Headers
set ( PROJECT_HEADERS "${SOURCES_DIR}/main.hpp"
    # CONFIGS
    "${SOURCES_DIR}/pathfinder2d/cfg/pathfinder2d.hpp"
    # TILES
    "${SOURCES_DIR}/pathfinder2d/core/IMap2DEventsHandler.hxx"
    "${SOURCES_DIR}/pathfinder2d/core/IMap2D.hxx"
    "${SOURCES_DIR}/pathfinder2d/core/Map2D.hpp" )

# =================================================================================
# SOURCES
# =================================================================================

# Sources
set ( PROJECT_SOURCES "${SOURCES_DIR}/main.cpp"
    # TILES
    "${SOURCES_DIR}/pathfinder2d/core/IMap2D.cpp"
    "${SOURCES_DIR}/pathfinder2d/core/Map2D.cpp" )

# =================================================================================
# BUILD
# =================================================================================

# Create STATIC Library-Object
add_library ( ${PROJECT_NAME} STATIC ${PROJECT_HEADERS} ${PROJECT_SOURCES} )

# INFO
message ( STATUS "${PROJECT_NAME} - STATIC Library build." )