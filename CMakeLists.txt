cmake_minimum_required(VERSION 3.28.3)
project(CMakeProj C)

include("./cmake/main.cmake")

set(enable_linux ON)

add_subdirectory("${proj_root_dir}/projects/main")
add_subdirectory("${proj_root_dir}/projects/use_main")
