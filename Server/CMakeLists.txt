cmake_minimum_required(VERSION 3.22)
project(Scan)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../Socket socket_lib)

include_directories(${SOCKET_FILES})

set(SRCS main.cpp ServerSocket.h ServerSocket.cpp Scan.h Scan.cpp)
add_executable(scan_service ${SRCS})
target_link_libraries(scan_service socket_lib)
