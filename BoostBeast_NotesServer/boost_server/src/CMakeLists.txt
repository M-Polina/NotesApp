find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



add_library(boost_server_lib
        fail.cpp
        serveralgorythms.cpp
        Note.cpp
        Account.cpp
        JsonParser.cpp
        session.cpp
        listener.cpp
)

