add_executable_target("p04_coll")
	
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/")
	if(testing_build)
		add_subdirectory("./tests")
	endif()
endif()

