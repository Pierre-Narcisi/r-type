/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** CommonTcpSocket.cpp
*/

#include "TcpSocket.hpp"

namespace nw {

void	TcpSocket::connect(TcpEndpoint const &ep) {
	bool	isFail = true;

	if ((_sock = ep.createSocket()) == -1) {
		throw std::runtime_error(TcpSocket::getLastNetError());
	}
	this->_endpoint = ep;
	for (auto &cur: _endpoint._ai) {
		reinterpret_cast<sockaddr_in*>(cur.get())->sin_port = _endpoint._port;
		if (::connect(_sock, reinterpret_cast<const sockaddr*>(cur.get()), sizeof(*cur)) < 0)
			continue;
		isFail = false;
		break;
	}
	if (isFail)
		throw std::runtime_error(TcpSocket::getLastNetError());
	_init = true;
}

void	TcpSocket::write(char const *buffer, SOCK_BUFFER_LEN_TYPE len) {
	auto l = ::send(_sock, buffer, len, 0);
	
	/* if (isNonBloquant) */
	if (l <= 0) {
		this->close();
		throw std::runtime_error("Connection closed by peer");
	}
}

ssize_t TcpSocket::read(char *buffer, SOCK_BUFFER_LEN_TYPE len) {
	auto l = ::recv(_sock, buffer, len, 0);
	
	/*TODO: if (isNonBloquant) */
	if (l <= 0) {
		this->close();
		throw std::runtime_error("Connection closed by peer");
	}
	return l;
}

bool	TcpSocket::isConnected() {
	int			error = 0;
	socklen_t	__len = sizeof(error);
	
	if (!_init) return (false);
	int retval = getsockopt(_sock, SOL_SOCKET, SO_ERROR, (char*) &error, &__len);
	if (retval != 0 || error != 0) {
		this->close();
		return (false);
	}
	return (true);
}

void	TcpSocket::close() {
	if (_init) {
		SOCKETCLOSE(_sock);
		_init = false;
	}
}

int	TcpSocket::available() {
	int	count = 0;

	SOCKETIOCTL(_sock, FIONREAD, &count);
	return (count);
}

}