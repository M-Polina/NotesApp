cmake_minimum_required(VERSION 3.26)
project(boost_server)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_executable(boost_server main.cpp)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})


target_include_directories(boost_server PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(boost_server ${Boost_LIBRARIES})

target_link_libraries(boost_server PRIVATE boost_server_lib)

target_include_directories(boost_server PRIVATE src)
