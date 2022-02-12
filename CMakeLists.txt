cmake_minimum_required(VERSION 3.10)
project(example VERSION 1.0.0 DESCRIPTION "example description")

set(PLATFORM "native" CACHE STRING "The target platform for the build")
set_property(CACHE PLATFORM PROPERTY STRINGS native web)

message(STATUS "Selected platform: ${PLATFORM}")
message(STATUS "Selected build type: ${CMAKE_BUILD_TYPE}")

if(PLATFORM STREQUAL "web")
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# output compiler info
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, ${CMAKE_CXX_COMPILER}")

# for all targets: use strict warnings and treat them as errors
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# set compiler options specific for debug build

# instrument code for coverage analysis
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
endif()
# enable memory checks
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
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



