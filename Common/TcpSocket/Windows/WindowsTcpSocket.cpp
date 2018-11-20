/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpSocket.cpp
*/

#include "WindowsTcpSocket.hpp"

#if defined(_INTERN_TCP_SOCKET_HPP)

#include <iostream>
#include <stdexcept>
#include <io.h> 
#include "TcpSocket.hpp"
#include "ctor.h"
#pragma comment(lib, "ws2_32.lib")

static WSADATA wsaData;

namespace nw {

static inline char *getWSAErrorString() {
	static char s[1024];

	*s = 0;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		s,
		sizeof(s),
		nullptr);
	return (s);
}

const char	*TcpSocket::getLastNetError() {
	return (getWSAErrorString());
}

void	TcpSocket::close() {
	if (_init) {
		closesocket(_endpoint._fd);
		_init = false;
	}
}

#ifdef HAS_CONSTRUCTORS
CONSTRUCTOR(initWSA)
DESTRUCTOR(closeWSA)
#else
#ifdef _MSC_VER
static void initWSA(void);
static void closeWSA(void);
#pragma data_seg(".CRT$XCU")
static void (*msc_ctor)(void) = initWSA;
#pragma data_seg(".CRT$XPU")
static void (*msc_dtor)(void) = closeWSA;
#pragma data_seg()
#endif
#endif

void initWSA()
{
	auto res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != 0) {
        std::cerr << "WSAStartup failed with error: " << res << std::endl;
		exit(84);
    }
}
 
void closeWSA()
{
	WSACleanup();
}

}

#endif