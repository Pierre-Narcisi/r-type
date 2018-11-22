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
#define SOCKETIOCTL(fd, opts, ptr) ioctlsocket((fd), (opts), ((u_long*) ptr))

namespace nw {

class TcpSocket : public ATcpSocket {
public:
	TcpSocket() : ATcpSocket(Platform::WINDOWS) {}
	TcpSocket(TcpEndpoint const &ep): ATcpSocket(Platform::WINDOWS, ep) {}
	~TcpSocket() { this->close(); }

	virtual void	connect(const TcpEndpoint &ep) final;
	virtual void	write(char const *buffer, std::size_t len) final;
	virtual ssize_t	read(char *buffer, std::size_t len) final;
	virtual bool	isConnected() final;
	virtual void	close() final;

	int				available();

	static const char	*getLastNetError();
	static int			getErrno() { return WSAGetLastError(); }
};

}

#endif // _INTERN_TCP_SOCKET_HPP

#endif