/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpSocket.hpp
*/

#if defined _MSC_VER

#if !defined(_INTERN_TCP_SOCKET_HPP)
#define _INTERN_TCP_SOCKET_HPP

#include "Network/_Network.hpp"
#include "../ATcpSocket.hpp"

namespace nw {

class TcpSocket : public ATcpSocket {
public:
	TcpSocket() : ATcpSocket(Platform::WINDOWS) {}
	TcpSocket(Socket sock, TcpEndpoint const &ep): ATcpSocket(Platform::WINDOWS, sock, ep) {}
	~TcpSocket() { this->close(); }

	virtual void	connect(const TcpEndpoint &ep) final;
	virtual void	write(char const *buffer, SOCK_BUFFER_LEN_TYPE len) final;
	virtual ssize_t	read(char *buffer, SOCK_BUFFER_LEN_TYPE len) final;
	virtual bool	isConnected() final;
	virtual void	close() final;

	int				available();

	static const char	*getLastNetError();
	static int			getErrno() { return WSAGetLastError(); }
};

}

#endif // _INTERN_TCP_SOCKET_HPP

#endif
