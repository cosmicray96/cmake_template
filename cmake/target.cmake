function(target_files_public target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	file(GLOB_RECURSE files 
		"${targ_path}/inc/${target_name}/*.h"
	)
	set(${out_var} "${files}" PARENT_SCOPE)
endfunction()

function(target_files_private target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	file(GLOB_RECURSE files 
		"${targ_path}/src/${target_name}/*.h"
		"${targ_path}/src/${target_name}/*.c"
	)

	__target_feature_files_private(${target_name} feature_files)
	list(APPEND files ${feature_files})

	set(${out_var} "${files}" PARENT_SCOPE)
endfunction()

function(target_inc_dir_public target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	set(dirs 
		"${targ_path}/inc"
	)
	set(${out_var} "${dirs}" PARENT_SCOPE)
endfunction()

function(target_inc_dir_private target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	set(dirs 
		"${targ_path}/src"
	)

	set(${out_var} "${dirs}" PARENT_SCOPE)
endfunction()

function(__target_defines_common_private target_name out_var)
	set(defines "")
	list(APPEND defines "${target_name}_inside")
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_defines_static_public target_name out_var)
	set(defines 
		"${target_name}_static" 
	)
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_defines_static_private target_name out_var)
	__target_defines_common_private("${target_name}" defines)
	# space for more
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_defines_shared_public target_name out_var)
	set(defines 
		"${target_name}_shared" 
	)
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_defines_shared_private target_name out_var)
	__target_defines_common_private("${target_name}" defines)
	# space for more
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_defines_exe_private target_name out_var)
	__target_defines_common_private("${target_name}" defines)
	# space for more
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_simple_exe target_name)
	target_files_public(${target_name} pub_files)
	target_files_private(${target_name} priv_files)
	target_inc_dir_public(${target_name} pub_includes)
	target_inc_dir_private(${target_name} priv_includes)
	target_defines_exe_private(${target_name} priv_defs)

	add_executable(${target_name}
		${pub_files}
		${priv_files}
	)
	target_include_directories(${target_name}
		PUBLIC ${pub_includes}
		PRIVATE ${priv_includes}
	)
	target_compile_definitions(${target_name}
		PRIVATE ${priv_defs}
	)
endfunction()

function(target_simple_static target_name)

	target_files_public(${target_name} pub_files)
	target_files_private(${target_name} priv_files)
	target_inc_dir_public(${target_name} pub_includes)
	target_inc_dir_private(${target_name} priv_includes)
	target_defines_static_private(${target_name} priv_defs)
	target_defines_static_public(${target_name} pub_defs)

	add_library(${target_name} STATIC
		${pub_files}
		${priv_files}
	)
	target_include_directories(${target_name}
		PUBLIC ${pub_includes}
		PRIVATE ${priv_includes}
	)
	target_compile_definitions(${target_name}
		PUBLIC ${pub_defs}
		PRIVATE ${priv_defs}
	)
endfunction()

function(target_simple_shared target_name)
	target_files_public(${target_name} pub_files)
	target_files_private(${target_name} priv_files)
	target_inc_dir_public(${target_name} pub_includes)
	target_inc_dir_private(${target_name} priv_includes)
	target_defines_shared_private(${target_name} priv_defs)
	target_defines_shared_public(${target_name} pub_defs)

	add_library(${target_name} SHARED
		${pub_files}
		${priv_files}
	)
	target_include_directories(${target_name}
		PUBLIC ${pub_includes}
		PRIVATE ${priv_includes}
	)
	target_compile_definitions(${target_name}
		PUBLIC ${pub_defs}
		PRIVATE ${priv_defs}
	)
endfunction()

