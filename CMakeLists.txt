cmake_minimum_required(VERSION 3.15)
project(CoolProject C)

# Use C11 and strict warnings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Later: include(helper modules here)
include("${CMAKE_CURRENT_LIST_DIR}/cmake/common.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/add_defines.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/add_target.cmake")

# Add subprojects
add_subdirectory(projects/project01)
add_subdirectory(projects/project03)
add_subdirectory(projects/project02)
