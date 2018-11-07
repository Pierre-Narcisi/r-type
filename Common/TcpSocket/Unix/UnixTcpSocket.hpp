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

struct TcpEndpoint {
	TcpEndpoint() = default;
	TcpEndpoint(std::string const ip, std::uint16_t port) {
		hostent		*hostinfo;
		
		if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			throw std::runtime_error(std::strerror(errno));
		srvAddr.sin_family = AF_INET;
    	srvAddr.sin_port = htons(port);
		if ((hostinfo = gethostbyname(ip.c_str())) == nullptr)
			throw std::runtime_error(std::strerror(errno));
		srvAddr.sin_addr = *(reinterpret_cast<in_addr*>(hostinfo->h_addr));
	};
	TcpEndpoint(TcpEndpoint const &) = default;
	TcpEndpoint(TcpEndpoint &&) = default;
	TcpEndpoint &operator=(TcpEndpoint const &) = default;

	std::string		getIpAsString() const { return inet_ntoa(srvAddr.sin_addr); }
	std::uint16_t	getPort() const { return ntohs(srvAddr.sin_port); }

	sockaddr_in	srvAddr;
	int			fd;
};

class TcpSocket : public ITcpSocket {
public:
	TcpSocket(): ITcpSocket(Platform::UNIX) {}
	~TcpSocket() { this->close(); }

	virtual void	connect(const TcpEndpoint &ep) final;
	virtual void	write(char const *buffer, std::size_t len) final;
	virtual ssize_t	read(char *buffer, std::size_t len) final;
	virtual bool	isConnected() final;
	virtual void	close() final;
private:
	TcpEndpoint		_endpoint;
	bool			_init = false;
};

}

#endif // _INTERN_TCP_SOCKET_HPP

#endif
