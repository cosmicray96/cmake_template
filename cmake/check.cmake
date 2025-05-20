
if(NOT CMAKE_C_COMPILER)
	message(FATAL_ERROR "C compiler not found!")
endif()


if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
	message(FATAL_ERROR "Only builds for linux is supported!")
endif()

if(NOT CMAKE_C_COMPILER_ID STREQUAL "GNU")
	message(FATAL_ERROR "Only Gnu C compiler is supported!")
endif()
