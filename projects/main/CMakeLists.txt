target_files_public(main pub_files)
target_files_private(main priv_files)
target_inc_dir_public(main pub_includes)
target_inc_dir_private(main priv_includes)
target_defines_private(main priv_defs)

add_library(main STATIC
    ${pub_files}
    ${priv_files}
)
target_include_directories(main
    PUBLIC ${pub_includes}
    PRIVATE ${priv_includes}
)
target_compile_definitions(main
    PRIVATE ${priv_defs}
)

if(BUILD_TESTS)
	add_subdirectory("./tests")
endif()

