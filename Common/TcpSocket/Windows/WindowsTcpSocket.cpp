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

void	TcpSocket::connect(TcpEndpoint const &ep) {
	if (::connect(ep.fd, reinterpret_cast<const sockaddr*>(&ep.srvAddr), sizeof(ep.srvAddr)) == SOCKET_ERROR) {
		closesocket(ep.fd);
		throw std::runtime_error(std::strerror(errno));
	}
	_endpoint = ep;
	_init = true;
}

void	TcpSocket::write(char const *buffer, std::size_t len) {
	auto l = send(_endpoint.fd, buffer, len, 0);

	/* if (isNonBloquant) */
	if (l == 0) {
		this->close();
		throw std::runtime_error("Connection closed by peer");
	}
}

ssize_t TcpSocket::read(char *buffer, std::size_t len) {
	auto l = ::recv(_endpoint.fd, buffer, len, 0);

	/*TODO: if (isNonBloquant) */
	if (l == 0) {
		this->close();
		throw std::runtime_error("Connection closed by peer");
	}
	return l;
}

bool	TcpSocket::isConnected() {
	char		error = 0;
	socklen_t	__len = sizeof(error);

	if (!_init) return (false);
	int retval = getsockopt(_endpoint.fd, SOL_SOCKET, SO_ERROR, &error, &__len);
	if (retval != 0 || error != 0) {
		this->close();
		return (false);
	}
	return (true);
}

void	TcpSocket::close() {
	if (_init) {
		closesocket(_endpoint.fd);
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