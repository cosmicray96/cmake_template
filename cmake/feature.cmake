function(__target_feature_files_private target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	set(files "")

	if(enable_window)
		file(GLOB_RECURSE window_files 
			"${targ_path}/src/${target_name}_window/*.h"
			"${targ_path}/src/${target_name}_window/*.c"
		)
		list(APPEND files ${window_files})
	endif()

	if(enable_linux)
		file(GLOB_RECURSE linux_files 
			"${targ_path}/src/${target_name}_linux/*.h"
			"${targ_path}/src/${target_name}_linux/*.c"
		)
		list(APPEND files ${linux_files})
	endif()

	set(${out_var} "${files}" PARENT_SCOPE)
endfunction()

