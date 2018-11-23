/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** UdpSocket.hpp
*/

#if !defined(_UDP_SOCKET_HPP)
#define _UDP_SOCKET_HPP

#include "../EndpointBase.hpp"

namespace nw {

class UdpSocket;

class UdpEndpoint: public EndpointBase {
public:
	UdpEndpoint():
		EndpointBase(AF_INET, SOCK_DGRAM, IPPROTO_UDP) {}
	UdpEndpoint(std::string const ip, std::uint16_t port):
		UdpEndpoint() { _fromIpPort(ip, port); }
	UdpEndpoint(struct sockaddr_in addr):
		UdpEndpoint() { _fromAddr(addr); }
	~UdpEndpoint() { }
	UdpEndpoint(UdpEndpoint const &) = default;
	UdpEndpoint(UdpEndpoint &&) = default;
	UdpEndpoint &operator=(UdpEndpoint const &) = default;

	static auto createSocket() {
		return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}
private:
	friend UdpSocket;
};

struct UdpBuffer {
	UdpBuffer(std::string &&str):
		buf(const_cast<char*>(str.c_str())), len(str.size() + 1) {}
	UdpBuffer(char *buffer, std::size_t size):
		buf(buffer), len(size) {}

	char		*buf;
	std::size_t	len;
};

class UdpSocket {
public:
	UdpSocket() = default;

	UdpEndpoint	sendTo(UdpBuffer const &buffer, UdpEndpoint const &ep);
	void		recvFrom(UdpBuffer &buffer, UdpEndpoint const &ep);

	int			setNonBlocking(bool isNonBlocking = true);
private:
	Socket	_sock = UdpEndpoint::createSocket();
};

}

#endif // _UDP_SOCKET_HPP
