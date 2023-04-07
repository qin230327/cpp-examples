cmake_minimum_required(VERSION 3.0)

project(cpp_examples)

set(CMAKE_CXX_STANDARD 11)

add_library(cpp_examples
        src/net/SocketClient.cpp
        src/net/SocketClient.h
        )