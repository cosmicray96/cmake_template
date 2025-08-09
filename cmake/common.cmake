
set(bin_dir "${proj_root_dir}/_bin")

set(junk_dir "${bin_dir}/${CMAKE_BUILD_TYPE}/_junk")
set(tests_dir "${bin_dir}/${CMAKE_BUILD_TYPE}/_tests")
set(bin_dir "${bin_dir}/${CMAKE_BUILD_TYPE}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${bin_dir}") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${bin_dir}") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${junk_dir}") 


