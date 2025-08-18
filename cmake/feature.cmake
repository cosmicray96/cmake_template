function(__get_features out_var)
	get_cmake_property(vars CACHE_VARIABLES)
	set(features "")
	foreach(var ${vars})
		if(NOT var MATCHES "^enable_")
			continue()
		endif()
		string(REGEX REPLACE "^enable_" "" fea "${var}")	
		list(APPEND features "${fea}")
	endforeach()
	list(SORT features)

	set(${out_var} "${features}" PARENT_SCOPE)
endfunction()

function(__get_bin_dir_name out_var)
	__get_features(features)
	if(features)
	string(JOIN "_" name ${features})
else()
	set(name "default")
endif()
	set(${out_var} "${name}" PARENT_SCOPE)
endfunction()


function(__target_feature_files_private target_name out_var)
	set(targ_path "${proj_root_dir}/projects/${target_name}")
	set(files "")
	__get_features(features)

	foreach(fea ${features})
		file(GLOB_RECURSE window_files 
			"${targ_path}/src/${target_name}_${fea}/*.h"
			"${targ_path}/src/${target_name}_${fea}/*.c"
		)
		list(APPEND files ${window_files})
	endforeach()

	set(${out_var} "${files}" PARENT_SCOPE)
endfunction()

