function(add_custom_test targ_name test_name)

target_files_public("${targ_name}" pub_files)
target_files_private("${targ_name}" priv_files)
target_inc_dir_public("${targ_name}" pub_includes)
target_inc_dir_private("${targ_name}" priv_includes)
target_defines_private("${targ_name}" priv_defs)

set(test_full_name "${targ_name}_${test_name}")

add_executable("${test_full_name}"
    ${pub_files}
    ${priv_files}
		"${proj_root_dir}/projects/${targ_name}/tests/${test_name}.c"
)
target_include_directories("${test_full_name}"
    PUBLIC ${pub_includes}
    PRIVATE ${priv_includes}
)
target_compile_definitions("${test_full_name}"
    PRIVATE ${priv_defs}
)

set_target_properties("${test_full_name}" PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${tests_dir}/${targ_name}"
)
get_target_property(pub_libs  "${targ_name}" INTERFACE_LINK_LIBRARIES)
get_target_property(priv_libs "${targ_name}" LINK_LIBRARIES)
if(pub_libs AND NOT pub_libs STREQUAL "NOTFOUND")
    target_link_libraries("${test_full_name}" PUBLIC ${pub_libs})
endif()

if(priv_libs AND NOT priv_libs STREQUAL "NOTFOUND")
    target_link_libraries("${test_full_name}" PRIVATE ${priv_libs})
endif()

add_test(NAME "${test_full_name}"
	COMMAND "${test_full_name}"
)

endfunction()
