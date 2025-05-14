
function(add_public_sources target_name)
	set(path_to_target "${CMAKE_SOURCE_DIR}/projects/${target_name}")
	
	file(GLOB_RECURSE target_sources_public 
		"${path_to_target}/inc/${target_name}/*.h"
	)
	target_sources(${target_name} 
		PUBLIC
			${target_sources_public}
	)	
endfunction()


function(add_private_sources target_name)
	set(path_to_target "${CMAKE_SOURCE_DIR}/projects/${target_name}")
	
	file(GLOB_RECURSE target_sources_private 
		"${path_to_target}/src/${target_name}/*.h"
		"${path_to_target}/src/${target_name}/*.c"
	)
	target_sources(${target_name} 
		PRIVATE
			${target_sources_private}
	)	
endfunction()


function(target_common target_name)
	
	set_target_properties(${target_name}
		PROPERTIES
			DEFINE_SYMBOL ""
	)
	
	# This ensures symbols are hidden by default on GCC/Clang
	set_target_properties(${target_name} PROPERTIES
		C_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN YES
	)

endfunction()


function(add_static_target target_name)
	
	add_library(${target_name} STATIC)
	target_common(${target_name})

	add_public_sources(${target_name})
	add_private_sources(${target_name})

	set(path_to_target "${CMAKE_SOURCE_DIR}/projects/${target_name}")
	target_include_directories(${target_name}
		PUBLIC
			"${path_to_target}/inc/"
		PRIVATE
			"${path_to_target}/src/"
	)

message("Target Added: ${target_name} (Static Library)")

endfunction()


function(add_executable_target target_name)
	
	add_executable(${target_name})
	target_common(${target_name})

	# add_public_sources(${target_name})
	add_private_sources(${target_name})

	set(path_to_target "${CMAKE_SOURCE_DIR}/projects/${target_name}")
	target_include_directories(${target_name}
		PUBLIC
			"${path_to_target}/inc/"
		PRIVATE
			"${path_to_target}/src/"
	)

message("Target Added: ${target_name} (Executable)")

endfunction()
