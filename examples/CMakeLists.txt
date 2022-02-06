set(CMAKE_CXX_STANDARD 17)

set(MY_SOURCE_FILES
	example1.cpp
	example2.cpp
)

foreach(SOURCE_PATH ${MY_SOURCE_FILES})

    get_filename_component(EXECUTABLE ${SOURCE_PATH} NAME_WE)

    add_executable(${EXECUTABLE} ${SOURCE_PATH})
	set_target_properties(${EXECUTABLE} PROPERTIES LINK_FLAGS "--emrun")
	target_include_directories(${EXECUTABLE} PRIVATE ../src/api)  # TODO the way to go?
	target_link_libraries(${EXECUTABLE} PUBLIC mylibrary)

endforeach(SOURCE_PATH ${SOURCE_FILES})




