cmake_minimum_required(VERSION 3.26)
project(BoostBeast_EchoServer)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(BoostBeast_EchoServer main.cpp)

target_include_directories(BoostBeast_EchoServer PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(BoostBeast_EchoServer ${Boost_LIBRARIES})

