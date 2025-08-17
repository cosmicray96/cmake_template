target_files_public(dyn_main pub_files)
target_files_private(dyn_main priv_files)
target_inc_dir_public(dyn_main pub_includes)
target_inc_dir_private(dyn_main priv_includes)
target_defines_shared_private(dyn_main priv_defs)
target_defines_shared_public(dyn_main pub_defs)

add_library(dyn_main SHARED
    ${pub_files}
    ${priv_files}
)
target_include_directories(dyn_main
    PUBLIC ${pub_includes}
    PRIVATE ${priv_includes}
)
target_compile_definitions(dyn_main
    PUBLIC ${pub_defs}
    PRIVATE ${priv_defs}
)


