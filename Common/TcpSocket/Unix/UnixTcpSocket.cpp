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

void	TcpSocket::connect(TcpEndpoint const &ep) {
	if (::connect(ep.fd, reinterpret_cast<const sockaddr*>(&ep.srvAddr), sizeof(ep.srvAddr)) < 0)
		throw std::runtime_error(std::strerror(errno));
	_endpoint = ep;
	_init = true;
}

void	TcpSocket::write(char const *buffer, std::size_t len) {
	auto l = ::write(_endpoint.fd, buffer, len);
	
	/* if (isNonBloquant) */
	if (l == 0) {
		this->close();
		throw std::runtime_error("Connection closed by peer");
	}
}

ssize_t TcpSocket::read(char *buffer, std::size_t len) {
	auto l = ::read(_endpoint.fd, buffer, len);
	
	/*TODO: if (isNonBloquant) */
	if (l == 0) {
		this->close();
		throw std::runtime_error("Connection closed by peer");
	}
	return l;
}

bool	TcpSocket::isConnected() {
	int			error = 0;
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
		::close(_endpoint.fd);
		_init = false;
	}
}

}

#endif