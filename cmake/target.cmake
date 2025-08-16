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

function(__target_defines_common target_name out_var)
	set(defines 
		"${target_name}_DEF"	
	)
	list(APPEND defines "${CMAKE_C_COMPILER_ID}")
	if(WIN32)
		list(APPEND defines "PLATFORM_WIN")
	elseif(UNIX)
		list(APPEND defines "PLATFORM_UNIX")
	endif()
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_defines_static_public target_name out_var)
	set(defines 
		"${target_name}_static" 
	)
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_defines_static_private target_name out_var)
	__target_defines_common("${target_name}" defines)
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
	__target_defines_common("${target_name}" defines)
	list(APPEND defines 
		"${target_name}_export" 
	)
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()

function(target_defines_exe_private target_name out_var)
	__target_defines_common("${target_name}" defines)
	# space for more
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()
