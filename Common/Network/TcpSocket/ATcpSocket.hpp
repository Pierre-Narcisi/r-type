/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ATcpSocket.hpp
*/

#if !defined(_ATCP_SOCKET_HPP)
#define _ATCP_SOCKET_HPP

#if defined _MSC_VER
#include <io.h>
using ssize_t = int;
#endif

#include <cstddef>
#include <list>
#include <memory>
#include <cstring>
#include <vector>
#include <mutex>
#include "../EndpointBase.hpp"

namespace nw {

class TcpSocket;

class TcpEndpoint: public EndpointBase {
public:
	TcpEndpoint():
		EndpointBase(AF_INET, SOCK_STREAM, IPPROTO_TCP) {}
	TcpEndpoint(std::string const ip, std::uint16_t port):
		TcpEndpoint() { _fromIpPort(ip, port); }
	TcpEndpoint(struct sockaddr_in addr):
		TcpEndpoint() { _fromAddr(addr); }
	~TcpEndpoint() { }
	TcpEndpoint(TcpEndpoint const &) = default;
	TcpEndpoint(TcpEndpoint &&) = default;
	TcpEndpoint &operator=(TcpEndpoint const &) = default;

	static auto createSocket() {
		return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
private:
	friend TcpSocket;
};

class ATcpSocket {
public:
	enum class Platform {
		WINDOWS,
		UNIX
	};

	ATcpSocket(Platform p): _platform(p), _init(false) {}
	ATcpSocket(Platform p, Socket socket, TcpEndpoint const &ep):
		_sock(socket), _platform(p), _endpoint(ep), _init(true) {}  

	virtual void	connect(const TcpEndpoint &ep) = 0;
	virtual void	write(char const *buffer, std::size_t len) = 0;
	virtual ssize_t	read(char *buffer, std::size_t len) = 0;
	virtual bool	isConnected() = 0;
	virtual void	close() = 0;

	Platform		getPlatfrom(void) { return _platform; }
protected:
	Socket		_sock;
	Platform	_platform;
	TcpEndpoint	_endpoint;
	bool		_init;
};

}

#endif // _ATCP_SOCKET_HPP