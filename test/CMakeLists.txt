set(CMAKE_CXX_STANDARD 17)

# https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html

add_subdirectory("${PROJECT_SOURCE_DIR}/libs/googletest" "libs/googletest")

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

macro(package_add_test TESTNAME)
    # create an exectuable in which the tests will be stored
    add_executable(${TESTNAME} ${ARGN})
	# includes for our own library
	target_include_directories(${TESTNAME} PRIVATE ../src)  # TODO the way to go?
    # link the Google test infrastructure, mocking library, and a default main fuction to
    # the test executable.  Remove g_test_main if writing your own main function.
    target_link_libraries(${TESTNAME} mylibrary gtest gmock gtest_main)
    # gtest_discover_tests replaces gtest_add_tests,
    # see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html for more options to pass to it
	if(NOT PLATFORM STREQUAL "web") # TODO discovery does not work for emscripten?
		gtest_discover_tests(${TESTNAME}
			# set a working directory so your project root so that you can find test data via paths relative to the project root
			WORKING_DIRECTORY ${PROJECT_DIR}
			PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
		)
	endif()
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
	
	if(PLATFORM STREQUAL "web")	
		set_target_properties(${TESTNAME} PROPERTIES LINK_FLAGS "--emrun")
	endif()	
endmacro()

package_add_test(unittest unittest.cpp inplace_pimpl.test.cpp command.test.cpp active.test.cpp utils/copy_tracker.cpp)
