cmake_minimum_required(VERSION 3.26)
project(tests)
get_directory_property(IS_SUBPROJECT "/Users/andreymarusin/Polina/C_plus_Labs/BoostBeast_EchoServer")

add_subdirectory(googletest)
include_directories(googletest/googletest/include "/Users/andreymarusin/Polina/C_plus_Labs/BoostBeast_EchoServer")
option(tests "Включить модульное тестирование" ON)

set(CMAKE_CXX_STANDARD 17)

add_executable(tests main.cpp)
target_link_libraries(tests gtest gtest_main)

