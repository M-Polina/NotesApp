cmake_minimum_required(VERSION 3.26)
project(server_tests)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)


set(CMAKE_CXX_STANDARD 17)

add_executable(server_tests
        main.cpp
        JsonParser.cpp
        ServerAlgorythms.cpp
        Account.cpp
        Note.cpp
)

target_link_libraries(server_tests PRIVATE gtest gtest_main)
target_link_libraries(server_tests PRIVATE boost_server_lib)

target_include_directories(server_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(../boost_server)
