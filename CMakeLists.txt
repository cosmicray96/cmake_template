cmake_minimum_required(VERSION 3.28.3)
project(CMakeProj C)

set(CMAKE_C_STANDARD "99")
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Absolute path to repo root (source tree)
set(proj_root_dir "${CMAKE_CURRENT_SOURCE_DIR}")
option(BUILD_TESTS "build all tests" ON)
enable_testing()

include("${proj_root_dir}/cmake/common.cmake")
include("${proj_root_dir}/cmake/target.cmake")
include("${proj_root_dir}/cmake/tests.cmake")

add_subdirectory("${proj_root_dir}/projects/main")
