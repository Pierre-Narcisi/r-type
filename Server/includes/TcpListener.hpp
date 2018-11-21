/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpListener.hpp
*/


#if !defined(_TCPLISTENER_HPP)
#define _TCPLISTENER_HPP

#include <functional>

namespace nw {

class TcpListenerSalve {
	
};

template<typename T>
class TcpListener {
public:
	using Error = int;
	using NewConnectionHandler = std::function<void(Error, T&)>;
	using DataAvailableHandler = std::function<void(Error, T&)>;

	TcpListener(std::uint16_t port): _port(port) {}

	void	run();
public:
	NewConnectionHandler onNewConnection;
	DataAvailableHandler onDataAvailable;

private:
	std::uint16_t	_port;
};

template<typename T>
void	TcpListener<T>::run() {

}

}

#endif // _TCPLISTENER_HPP
