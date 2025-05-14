add_executable_target("project02")
target_link_library("project02" 
	PRIVATE
		"project01")
