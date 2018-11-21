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
#include <memory>
#include <list>
#include "TcpSocket/TcpSocket.hpp"

namespace nw {

class TcpListenerSalve {
public:
	using NativeAddr = struct sockaddr_in;
	using NativeSocket = int;

	explicit TcpListenerSalve(int socketFd, NativeAddr const &addr):
		_nativeSock(socketFd), _addr(addr), _sock(TcpEndpoint(socketFd, addr)) {}

	template <typename T>
	void	setIterator(T const &it) {
		_iterator = std::shared_ptr<T>(new T(it));
	}
	template <typename T>
	auto	getIterator() {
		return *reinterpret_cast<T*>(_iterator.get());
	}

	NativeSocket	getNativeSocket() { return _nativeSock; }
	auto			&getSocket() { return _sock; }
	virtual void	onDataAvailable() = 0;
protected:
	NativeSocket			_nativeSock;
	NativeAddr				_addr;
	TcpSocket				_sock;
	std::shared_ptr<void>	_iterator;
};

template<typename T = TcpListenerSalve>
class TcpListener {
public:
	using Error = int;
	using NewConnectionHandler = std::function<void(T&)>;
	using DataAvailableHandler = std::function<void(T&)>;

	TcpListener(std::uint16_t port): _port(port) {}
	~TcpListener();

	void	init();
	void	run();
private: //members
	void	_accept();
public:
	NewConnectionHandler onNewConnection;
	DataAvailableHandler onDataAvailable;

private:
	std::uint16_t	_port;
	int				_socketFd;
	bool			_continue = true;
	std::list<T>	_slaves;
};

}

#include "TcpListener.tpp"

#endif // _TCPLISTENER_HPP
