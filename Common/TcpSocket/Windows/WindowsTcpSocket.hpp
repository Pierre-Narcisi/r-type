/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpSocket.hpp
*/

#if defined _MSC_VER

#if !defined(_INTERN_TCP_SOCKET_HPP)
#define _INTERN_TCP_SOCKET_HPP

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <windows.h>
#include "../ATcpSocket.hpp"

#define SOCKETCLOSE(fd) closesocket((fd))

namespace nw {

class TcpSocket : public ATcpSocket {
public:
	TcpSocket() : ATcpSocket(Platform::UNIX) {}
	~TcpSocket() { this->close(); }

	virtual void	connect(const TcpEndpoint &ep) final;
	virtual void	write(char const *buffer, std::size_t len) final;
	virtual ssize_t	read(char *buffer, std::size_t len) final;
	virtual bool	isConnected() final;
	virtual void	close() final;

	static const char	*getLastNetError();
};

}

#endif // _INTERN_TCP_SOCKET_HPP

#endif
