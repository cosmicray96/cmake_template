set(CMAKE_C_STANDARD "99")
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

enable_testing()

get_filename_component(proj_root_dir "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

#--- output dirs ---#
set(bin_dir "${proj_root_dir}/_bin")

set(junk_dir "${bin_dir}/${CMAKE_BUILD_TYPE}/_junk")
set(tests_dir "${bin_dir}/${CMAKE_BUILD_TYPE}/_tests")
set(exe_dir "${bin_dir}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${exe_dir}") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${exe_dir}") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${junk_dir}") 

#--- clangd ---#
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${proj_root_dir}/compile_commands.json
    COMMENT "Copying compile_commands.json to project root"
    VERBATIM
)

