/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ITcpSocket.hpp
*/

#if !defined(_ITCP_SOCKET_HPP)
#define _ITCP_SOCKET_HPP

#if defined _MSC_VER
#include <io.h>
using ssize_t = int;
#endif

#include <cstddef>

namespace nw {

class TcpEndpoint;

class ITcpSocket {
public:
	enum class Platform {
		WINDOWS,
		UNIX
	};

	ITcpSocket(Platform p): _platform(p) {} 

	virtual void	connect(const TcpEndpoint &ep) = 0;
	virtual void	write(char const *buffer, std::size_t len) = 0;
	virtual ssize_t	read(char *buffer, std::size_t len) = 0;
	virtual bool	isConnected() = 0;
	virtual void	close() = 0;

	Platform	getPlatfrom(void) { return _platform; }
protected:
	Platform	_platform;

};

}

#endif // _ITCP_SOCKET_HPP