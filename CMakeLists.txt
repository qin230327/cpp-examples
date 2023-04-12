cmake_minimum_required(VERSION 3.0)

option(ENABLE_VCPKG_SUPPORT "whether to use VCPKG to manage dependencies" OFF)
if (WIN32)
        if (ENABLE_VCPKG_SUPPORT)
                message("using VCPKG to manage dependencies.")
                if (NOT DEFINED VCPKG_ROOT)
                        message("[ERROR] VCPKG_ROOT is not defined, please set the root of vcpkg.cmake file to VCPKG_ROOT.")
                else()
                        set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})
                        message(VCPKG_ROOT:${VCPKG_ROOT})
                endif()
                if (NOT DEFINED VCPKG_TARGET_TRIPLET)
                        message("[ERROR] VCPKG_TARGET_TRIPLET is not defined, using default VCPKG_TARGET_TRIPLET x64-windows.")
                        set(VCPKG_TARGET_TRIPLET x64-windows)
                else()
                        message(VCPKG_TARGET_TRIPLET:${VCPKG_TARGET_TRIPLET})
                endif()
                message(CMAKE_TOOLCHAIN_FILE:${CMAKE_TOOLCHAIN_FILE})
        endif()
endif()


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