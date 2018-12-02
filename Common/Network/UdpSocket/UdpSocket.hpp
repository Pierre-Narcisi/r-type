/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** UdpSocket.hpp
*/

#if !defined(_UDP_SOCKET_HPP)
#define _UDP_SOCKET_HPP

#include <mutex>
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
	UdpSocket(): _sock(UdpEndpoint::createSocket()) {}
	~UdpSocket();

	UdpEndpoint	sendTo(UdpBuffer const &buffer, UdpEndpoint const &ep);
	long		recvFrom(UdpBuffer &buffer, UdpEndpoint &ep);

	int				setNonBlocking(bool isNonBlocking = true);
	std::uint16_t	makeMeAsListener(std::uint16_t port = 0); // if port = 0, port is auto generated
private:
	Socket		_sock;
	bool		_isListener = false;
	std::mutex	_udpMutex;
};

}

#endif // _UDP_SOCKET_HPP
