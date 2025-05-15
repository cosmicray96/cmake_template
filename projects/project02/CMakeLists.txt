add_executable_target("project02")
target_link_libraries("project02" 
	PRIVATE
		"project01")
target_link_libraries("project02" 
	PRIVATE
		"project03")
