cmake_minimum_required(VERSION 3.0)

project(cpp_examples)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED)
if (${Boost_FOUND})
message("found boost") 
message(boost_version:${Boost_VERSION})
message(boost_include_dirs:${Boost_INCLUDE_DIRS})
else()
message("ERROR!!! CANNOT FIND BOOST.")
endif()

add_library(cpp_examples
        src/net/TcpClient.cpp
        src/net/TcpClient.h
        src/net/TcpServer.cpp
        src/net/TcpServer.h
        )