cmake_minimum_required(VERSION 3.0)
project(example VERSION 1.0.0 DESCRIPTION "example description")

set(PLATFORM "native" CACHE STRING "The target platform for the build")
set_property(CACHE PLATFORM PROPERTY STRINGS native web)

message(STATUS "Selected platform: ${PLATFORM}")

if(PLATFORM STREQUAL "web")
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# include our libary
add_subdirectory(src)

# include tests (optional)
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" # emscripten?
    add_subdirectory(test)
endif()

# include examples
add_subdirectory(examples)



