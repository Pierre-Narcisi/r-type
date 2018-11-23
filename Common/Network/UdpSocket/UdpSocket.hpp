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
private:
	friend UdpSocket;
};

class UdpSocket {
public:
	UdpSocket();

	void		send(char *buffer, std::size_t len);
	UdpEndpoint	sendTo(char *buffer, std::size_t len);
private:
};

}

#endif // _UDP_SOCKET_HPP
