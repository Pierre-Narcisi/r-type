/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpListener.hpp
*/


#if !defined(_TCPLISTENER_TPP)
#define _TCPLISTENER_TPP

#include <time.h>
#include "TcpListener.hpp"

#include <iostream>
namespace nw {

template<typename T>
TcpListener<T>::~TcpListener() {
	for (auto it = _slaves.begin(); it != _slaves.end();) {
		auto next = it;

		next++;
		_slaves.erase(it);
		it = next;
	}

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
	char opt = 1;
	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
    	throw std::runtime_error(TcpSocket::getLastNetError());
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
	int					err = 0;
	int					clientFd = -1;
	struct sockaddr_in	clientAddr;
	socklen_t			clientAddrLen = sizeof(clientAddr);

	err = (clientFd = accept(
		_socketFd, (struct sockaddr*) &clientAddr, &clientAddrLen));
	if (err == -1) {
		throw std::runtime_error(TcpSocket::getLastNetError());
	}

	auto &slaveRef = _slaves.emplace_back(clientFd, clientAddr);
	slaveRef.setIterator(--_slaves.end());
	if (onNewConnection) onNewConnection(slaveRef);
}

template<typename T>
void	TcpListener<T>::run() {
	fd_set			rfds;

	_continue = true;
	while (_continue) {
		struct timeval	tv = {0, 100000};

		FD_ZERO(&rfds);
		FD_SET(_socketFd, &rfds);
		for (auto &slave: _slaves)
			FD_SET(slave.getNativeSocket(), &rfds);
		if (int rc; (rc = select(FD_SETSIZE, &rfds, NULL, NULL, &tv)) > 0) {
		} else if (rc == 0 || TcpSocket::getErrno() == EINTR) {
			continue;
		} else {
			throw std::runtime_error(TcpSocket::getLastNetError());
		}
		if (FD_ISSET(_socketFd, &rfds)) {
			this->_accept();
		}
		for (auto next = _slaves.begin(); next != _slaves.end();) {
			auto it = next++;
			auto &slave = *(it);

			if (FD_ISSET(slave.getNativeSocket(), &rfds)) {
				auto len = slave.getSocket().available();

				if (len != 0) {
					if (onDataAvailable) onDataAvailable(slave, len);
					slave.onDataAvailable(len);
				} else {
					std::cout << "Client disconnected" << std::endl;
					_slaves.erase(slave.template getIterator<typename decltype(_slaves)::iterator>());
				}
			}
		}
	}
}

}

#endif // _TCPLISTENER_TPP
