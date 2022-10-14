cmake_minimum_required(VERSION 3.22)
project(Scan)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../Socket socket_lib)

include_directories(${SOCKET_FILES})

set(SRCS_CLIENT main.cpp ClientSocket.cpp ClientSocket.h)
add_executable(client ${SRCS_CLIENT})
target_link_libraries(client socket_lib)

