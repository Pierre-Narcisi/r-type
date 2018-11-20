/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** TcpSocket.hpp
*/

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))

#if !defined(_INTERN_TCP_SOCKET_HPP)
#define _INTERN_TCP_SOCKET_HPP

#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <stdexcept>
#include <errno.h>
#include "../ITcpSocket.hpp"

namespace nw {

class TcpSocket : public ITcpSocket {
public:
	TcpSocket(): ITcpSocket(Platform::UNIX) {}
	~TcpSocket() { this->close(); }

	virtual void	connect(const TcpEndpoint &ep) final;
	virtual void	write(char const *buffer, std::size_t len) final;
	virtual ssize_t	read(char *buffer, std::size_t len) final;
	virtual bool	isConnected() final;
	virtual void	close() final;
};

}

#endif // _INTERN_TCP_SOCKET_HPP

#endif
