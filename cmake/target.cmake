function(target_files_public target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	file(GLOB_RECURSE files 
		"${targ_path}/inc/${target_name}/*.h"
	)
	# more glob for each conditional section like windows or linux
	set(${out_var} "${files}" PARENT_SCOPE)
endfunction()

function(target_files_private target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	file(GLOB_RECURSE files 
		"${targ_path}/src/${target_name}/*.h"
		"${targ_path}/src/${target_name}/*.c"
	)
	# more glob for each conditional section like windows or linux
	set(${out_var} "${files}" PARENT_SCOPE)
endfunction()

function(target_inc_dir_public target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	set(dirs 
		"${targ_path}/inc"
	)
	# more glob for each conditional section like windows or linux
	set(${out_var} "${dirs}" PARENT_SCOPE)
endfunction()

function(target_inc_dir_private target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	set(dirs 
		"${targ_path}/src"
	)
	# more glob for each conditional section like windows or linux
	set(${out_var} "${dirs}" PARENT_SCOPE)
endfunction()

function(target_defines_private target_name out_var)
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

function(target_defines_shared_private target_name out_var)

	target_defines_private("${target_name}" defines)
	list(APPEND defines 
		"${target_name}_exp"
	)
	set(${out_var} "${defines}" PARENT_SCOPE)
endfunction()
