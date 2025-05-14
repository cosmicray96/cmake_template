
set(output_directory "${CMAKE_SOURCE_DIR}/_outputs")
set(cmake_build_configs Debug Release RelWithDebInfo MinSizeRel)


foreach(build_config IN LISTS build_configs)
	string(TOUPPER ${build_config} config_u)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config_u} ${output_directory}/${build_config})
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config_u} ${output_directory}/${build_config})
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config_u} ${output_directory}/${build_config}/_junk)
endforeach()


