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
#include <list>
#include "Network/TcpSocket/TcpSocket.hpp"

namespace nw {

template<typename T>
class TcpListener {
public:
	using Error = int;
	using NewConnectionHandler = std::function<void(T&)>;
	using DataAvailableHandler = std::function<void(T&, std::size_t len)>;

	TcpListener(std::uint16_t port): _port(port) {}
	~TcpListener();

	void	init();
	void	run();
	void	stop() { _continue = false; }
	auto	&getSlaves() { return _slaves; }
private: //members
	void	_accept();
public:
	NewConnectionHandler onNewConnection;
	DataAvailableHandler onDataAvailable;

private:
	std::uint16_t	_port;
	int				_socketFd;
	bool			_continue;
	std::list<T>	_slaves;
};

}

#include "TcpListener.tpp"

#endif // _TCPLISTENER_HPP
