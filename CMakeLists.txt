cmake_minimum_required(VERSION 3.0)
project(example)

set(CMAKE_EXECUTABLE_SUFFIX ".html")

# add our file
add_executable(example ${MY_SRC_FILE})
set_target_properties(example PROPERTIES OUTPUT_NAME ${MY_EXEC_NAME})

set_target_properties(example PROPERTIES LINK_FLAGS "--emrun")

# google benchmark
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(libs/benchmark)# libs/benchmark EXCLUDE_FROM_ALL)
target_link_libraries(example benchmark::benchmark)
