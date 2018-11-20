/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpSocket.cpp
*/

#include "UnixTcpSocket.hpp"

#if defined(_INTERN_TCP_SOCKET_HPP)

#include <unistd.h>

namespace nw {

const char	*TcpSocket::getLastNetError() {
	auto err = errno;

	errno = 0;
	return (std::strerror(err));
}

void	TcpSocket::close() {
	if (_init) {
		::close(_endpoint._fd);
		_init = false;
	}
}

}

#endif