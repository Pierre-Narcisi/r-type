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

void	TcpSocket::connect(TcpEndpoint const &ep) {
	bool	isFail = true;
	char	s[256];

	if (ep._fd == -1) {
		throw std::runtime_error(getWSAErrorString());
	}
	this->_endpoint = ep;
	for (auto &cur: _endpoint._ai) {
		reinterpret_cast<sockaddr_in*>(cur.get())->sin_port = _endpoint._port;
		if (::connect(_endpoint._fd, reinterpret_cast<const sockaddr*>(cur.get()), sizeof(*cur)) < 0)
			continue;
		isFail = false;
		break;
	}
	if (isFail)
		throw std::runtime_error(getWSAErrorString());
	_init = true;
}

void	TcpSocket::write(char const *buffer, std::size_t len) {
	auto l = send(_endpoint._fd, buffer, len, 0);

	/* if (isNonBloquant) */
	if (l == 0) {
		this->close();
		throw std::runtime_error(getWSAErrorString());
	}
}

ssize_t TcpSocket::read(char *buffer, std::size_t len) {
	auto l = ::recv(_endpoint._fd, buffer, len, 0);

	/*TODO: if (isNonBloquant) */
	if (l == 0) {
		this->close();
		throw std::runtime_error(getWSAErrorString());
	}
	return l;
}

bool	TcpSocket::isConnected() {
	char		error = 0;
	socklen_t	__len = sizeof(error);

	if (!_init) return (false);
	int retval = getsockopt(_endpoint._fd, SOL_SOCKET, SO_ERROR, &error, &__len);
	if (retval != 0 || error != 0) {
		this->close();
		return (false);
	}
	return (true);
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