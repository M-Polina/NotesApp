cmake_minimum_required(VERSION 3.26)
project(BoostBeast_EchoServer)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(BoostBeast_EchoServer main.cpp nlohmann/json.hpp
        JsonParser.cpp
        JsonParser.h
        listener.cpp
        listener.h
        fail.cpp
        fail.h
        session.cpp
        session.h
        Note.cpp
        Note.h
        Account.cpp
        Account.h
        ServerAlgorythms.cpp
        ServerAlgorythms.h
)

target_include_directories(BoostBeast_EchoServer PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(BoostBeast_EchoServer ${Boost_LIBRARIES})

