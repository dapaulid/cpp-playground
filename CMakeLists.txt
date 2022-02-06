cmake_minimum_required(VERSION 3.0)
project(example VERSION 1.0.0 DESCRIPTION "example description")

# emscripten
set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_subdirectory(src)
add_subdirectory(examples)

# google benchmark
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(libs/benchmark)# libs/benchmark EXCLUDE_FROM_ALL)

# google test
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_subdirectory(libs/googletest)
enable_testing()


# our stuff
set (CMAKE_CXX_STANDARD 11)



# add our file
add_executable(example src/main.cpp src/threadinfo.cpp)

set_target_properties(example PROPERTIES OUTPUT_NAME example)
set_target_properties(example PROPERTIES COMPILE_FLAGS "-s USE_PTHREADS")
set_target_properties(example PROPERTIES LINK_FLAGS "--emrun -s NO_EXIT_RUNTIME -s USE_PTHREADS -s PROXY_TO_PTHREAD")

target_link_libraries(example -lwebsocket)
target_link_libraries(example benchmark::benchmark)

target_link_libraries(example gtest_main)
include(GoogleTest)
#gtest_discover_tests(example)   # fails on emscripten because test executable cannot be executed

