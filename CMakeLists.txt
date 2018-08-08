cmake_minimum_required(VERSION 2.6.4)
project(data-structures)
set (CMAKE_CXX_STANDARD 14)

enable_testing()
add_subdirectory( googletest )

# this sets the output dir to /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/googletest/include)
add_executable(dstest gtest-data-structures.cpp)
target_link_libraries(dstest gtest_main gtest)
