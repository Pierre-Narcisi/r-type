/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpListener.hpp
*/


#if !defined(_TCPLISTENER_TPP)
#define _TCPLISTENER_TPP

#include "TcpListener.hpp"

namespace nw {

template<typename T>
TcpListener<T>::~TcpListener() {
	// for (auto &salve: _slaves) {
	// 	salve.endConnection();
	// }

	SOCKETCLOSE(_socketFd);
}

template<typename T>
void	TcpListener<T>::init() {
	const auto			backlog = 128;
	struct sockaddr_in	serverAddr{ 0 };

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(_port);
	if ((_socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		throw std::runtime_error(TcpSocket::getLastNetError());
	}
	if (bind(_socketFd,
	(struct sockaddr*)&serverAddr,
	sizeof(serverAddr))) {
		throw std::runtime_error(TcpSocket::getLastNetError());
	}
	if (listen(_socketFd, backlog)) {
		throw std::runtime_error(TcpSocket::getLastNetError());
	}
}

template<typename T>
void	TcpListener<T>::_accept() {
	int								err = 0;
	int								clientFd = -1;
	TcpListenerSalve::NativeAddr	clientAddr;
	socklen_t						clientAddrLen = sizeof(clientAddr);

	err = (clientFd = accept(
		_socketFd, (struct sockaddr*) &clientAddr, &clientAddrLen));
	if (err == -1) {
		throw std::runtime_error(TcpSocket::getLastNetError());
	}

	auto &slaveRef = _slaves.emplace_back(clientFd, clientAddr);
	slaveRef.setIterator(_slaves.end()--);
	if (onNewConnection) onNewConnection(slaveRef);
}

template<typename T>
void	TcpListener<T>::run() {
	fd_set	rfds;

	while (_continue) {
		FD_ZERO(&rfds);
		FD_SET(_socketFd, &rfds);

		for (auto &slave: _slaves)
			FD_SET(slave.getNativeSocket(), &rfds);
		if (select(FD_SETSIZE, &rfds, NULL, NULL, NULL) < 0)
			std::runtime_error(TcpSocket::getLastNetError());
		if (FD_ISSET(_socketFd, &rfds)) {
			this->_accept();
		}
		for (auto &slave: _slaves) {
			if (FD_ISSET(slave.getNativeSocket(), &rfds)) {
				if (onDataAvailable) onDataAvailable(slave);
				slave.onDataAvailable();
			}
		}
	}
}

}

#endif // _TCPLISTENER_TPP
