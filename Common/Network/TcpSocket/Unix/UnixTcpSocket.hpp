/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpSocket.hpp
*/

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))

#if !defined(_INTERN_TCP_SOCKET_HPP)
#define _INTERN_TCP_SOCKET_HPP

#include "Network/_Network.hpp"
#include "../ATcpSocket.hpp"

namespace nw {

class TcpSocket : public ATcpSocket {
public:
	TcpSocket(): ATcpSocket(Platform::UNIX) {}
	TcpSocket(Socket sock, TcpEndpoint const &ep): ATcpSocket(Platform::UNIX, sock, ep) {}
	~TcpSocket() { this->close(); }

	virtual void	connect(const TcpEndpoint &ep) final;
	virtual void	write(char const *buffer, std::size_t len) final;
	virtual ssize_t	read(char *buffer, std::size_t len) final;
	virtual bool	isConnected() final;
	virtual void	close() final;

	int				available();

	static const char	*getLastNetError();
	static int			getErrno() { return errno; }
};

}

#endif // _INTERN_TCP_SOCKET_HPP

#endif
