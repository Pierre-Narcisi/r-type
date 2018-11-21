/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpListener.hpp
*/


#if !defined(_TCPLISTENER_HPP)
#define _TCPLISTENER_HPP

#include <functional>
#include <exception>
#include "TcpSocket/TcpSocket.hpp"

namespace nw {

class TcpListenerSalve {

};

template<typename T>
class TcpListener {
public:
	using Error = int;
	using NewConnectionHandler = std::function<void(T&)>;
	using DataAvailableHandler = std::function<void(Error, T&)>;

	TcpListener(std::uint16_t port): _port(port) {}

	void	run();
private: //members
	void	_init();

public:
	NewConnectionHandler onNewConnection;
	DataAvailableHandler onDataAvailable;

private:
	std::uint16_t	_port;
	int				_socketFd;
	bool			_continue = true;
};

template<typename T>
void	TcpListener<T>::_init() {
	const auto			backlog = 128;
	struct sockaddr_in	serverAddr = { 0 };

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(_port);
	if ((_socketFd = socket(AF_INET, SOCK_STREAM, 0))) {
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
void	TcpListener<T>::run() {
	int					err = 0;
	int					clientFd = -1;
	struct sockaddr_in	clientAddr;
	constexpr socklen_t	clientAddrLen = sizeof(clientAddr);

	_init();
	while (_continue) {
		err = (clientFd = accept(
			_socketFd, (struct sockaddr*) &clientAddr, &clientAddrLen));
		if (err == -1) {
			throw std::runtime_error(TcpSocket::getLastNetError());
		}

		(onNewConnection != nullptr) && onNewConnection(T(clientAddr));
	}
}

}

#endif // _TCPLISTENER_HPP
