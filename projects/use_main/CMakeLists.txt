target_files_public(use_main pub_files)
target_files_private(use_main priv_files)
target_inc_dir_public(use_main pub_includes)
target_inc_dir_private(use_main priv_includes)
target_defines_exe_private(use_main priv_defs)

add_executable(use_main
    ${pub_files}
    ${priv_files}
)
target_include_directories(use_main
    PUBLIC ${pub_includes}
    PRIVATE ${priv_includes}
)
target_compile_definitions(use_main
    PRIVATE ${priv_defs}
)

target_link_libraries(use_main 
	PRIVATE "main"
)

