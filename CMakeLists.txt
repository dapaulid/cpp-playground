cmake_minimum_required(VERSION 3.0)
project(example)

# google benchmark
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(libs/benchmark)# libs/benchmark EXCLUDE_FROM_ALL)


# our stuff
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_EXECUTABLE_SUFFIX ".html")

# add our file
add_executable(example src/main.cpp src/threadinfo.cpp)

set_target_properties(example PROPERTIES OUTPUT_NAME example)
set_target_properties(example PROPERTIES COMPILE_FLAGS "-s USE_PTHREADS")
set_target_properties(example PROPERTIES LINK_FLAGS "--emrun -s NO_EXIT_RUNTIME -s USE_PTHREADS -s PROXY_TO_PTHREAD")

target_link_libraries(example -lwebsocket)
target_link_libraries(example benchmark::benchmark)


