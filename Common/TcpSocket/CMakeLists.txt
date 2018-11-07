cmake_minimum_required(VERSION 3.10)
project(testTcpSocket)

set(CMAKE_CXX_STANDARD 17)

include_directories(..)
include_directories(.)

add_executable(testTcpSocket
	TestTcpSocket.cpp
	ITcpSocket.hpp
	TcpSocket.hpp
	Unix/UnixTcpSocket.cpp
	Unix/UnixTcpSocket.hpp
	Windows/WindowsTcpSocket.cpp
	Windows/WindowsTcpSocket.hpp
)