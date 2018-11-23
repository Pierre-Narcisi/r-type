/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpListener.hpp
*/


#if !defined(_TCPLISTENERSLAVE_HPP)
#define _TCPLISTENERSLAVE_HPP

#include <memory>
#include "Network/TcpSocket/TcpSocket.hpp"

namespace nw {

class TcpListenerSlave {
public:
	using NativeAddr = sockaddr_in;
	using NativeSocket = int;

	explicit TcpListenerSlave(int socketFd, NativeAddr const &addr):
		_nativeSock(socketFd), _addr(addr), _sock(socketFd, TcpEndpoint(addr)) {}

	~TcpListenerSlave() {
		_sock.close();
	}

	template <typename T>
	void	setIterator(T const &it) {
		_iterator = std::shared_ptr<T>(new T(it));
	}

	template <typename T>
	auto	getIterator() {
		return *reinterpret_cast<T*>(_iterator.get());
	}

	const NativeAddr	&getNativeAddr() const { return _addr; }
	NativeSocket		getNativeSocket() { return _nativeSock; }
	auto				&getSocket() { return _sock; }
	virtual void		onDataAvailable(std::size_t available) = 0;
protected:
	NativeSocket			_nativeSock;
	NativeAddr				_addr;
	TcpSocket				_sock;
	std::shared_ptr<void>	_iterator;
};

}


#endif // _TCPLISTENERSLAVE_HPP
