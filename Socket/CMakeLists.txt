cmake_minimum_required(VERSION 3.22)
project(Scan)

set(CMAKE_CXX_STANDARD 20)

set(SOCKET_FILES ${CMAKE_CURRENT_SOURCE_DIR})

if(TARGET socket_lib)

    message("socket is already defined")

else()

    include_directories(${SOCKET_FILES})

    set(LIB_SRCS ./Socket.cpp)

    add_library(socket_lib STATIC ${LIB_SRCS})

endif()
