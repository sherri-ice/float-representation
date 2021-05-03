cmake_minimum_required(VERSION 3.17)
project(float)

set(CMAKE_CXX_STANDARD 20)
# use for tests
# add_subdirectory(lib)
# include_directories(lib/googletest/include)
# include_directories(lib/googlemock/include)

add_executable( float float_internals.cpp
                float_internals.h
                float_internals_tests.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -fsanitize=address -fsanitize=undefined")

target_link_libraries(float gtest gtest_main)