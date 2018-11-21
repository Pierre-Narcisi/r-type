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

}

#endif