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

find_package(Boost)
if (${Boost_FOUND})
        message(STATUS "found boost") 
        message(STATUS "Boost_VERSION:${Boost_VERSION}")
        if ("${Boost_INCLUDE_DIRS}" STREQUAL "")
                message("[ERROR] Boost_INCLUDE_DIRS is empty.")
        else()
                message(STATUS "Boost_INCLUDE_DIRS:${Boost_INCLUDE_DIRS}")
        endif()
        if ("${Boost_LIBRARY_DIRS}" STREQUAL "")
                message("[ERROR] Boost_LIBRARY_DIRS is not defined")
        else()
                message(STATUS "Boost_LIBRARY_DIRS:${Boost_LIBRARY_DIRS}")
        endif()
else()
        message("[ERROR] CANNOT FIND BOOST.")
endif()
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_library(cpp_examples
        src/net/TcpClient.cpp
        src/net/TcpClient.h
        src/net/TcpServer.cpp
        src/net/TcpServer.h
        )

target_link_libraries(cpp_examples boost_system boost_thread pthread)