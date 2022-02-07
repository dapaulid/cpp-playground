set(CMAKE_CXX_STANDARD 17)

macro(package_add_example EXECUTABLE)
	add_executable(${EXECUTABLE} ${ARGN})
	target_include_directories(${EXECUTABLE} PRIVATE ../src/api)  # TODO the way to go?
	target_link_libraries(${EXECUTABLE} PUBLIC mylibrary)
	if(PLATFORM STREQUAL "web")	
		set_target_properties(${EXECUTABLE} PROPERTIES LINK_FLAGS "--emrun")
	endif()	
endmacro()

# list all examples with their sources here
package_add_example(example1 example1.cpp)
package_add_example(example2 example2.cpp)
