cmake_minimum_required(VERSION 3.0)

project(cpp_examples)

set(CMAKE_CXX_STANDARD 11)

include_directories(C:/boost_1_81_0)
link_libraries(C:/boost_1_81_0/stage/lib)

add_library(cpp_examples
        src/net/TcpClient.cpp
        src/net/TcpClient.h
        src/net/TcpServer.cpp
        src/net/TcpServer.h
        )