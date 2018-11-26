/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** UdpSocket.cpp
*/

#include <memory>
#include "UdpSocket.hpp"

namespace nw {

UdpEndpoint	UdpSocket::sendTo(UdpBuffer const &buffer, UdpEndpoint const &ep) {
	if (ep._ai.size() > 0) {
		auto		*curAddr = reinterpret_cast<sockaddr_in*>(ep._ai[0].get());
		auto		newAddr = *curAddr;
		
		newAddr.sin_port = ep._port;

		::sendto(_sock, buffer.buf, buffer.len, 0, (const sockaddr*)&newAddr, sizeof(newAddr));
		return (newAddr);
	} else {
		throw std::runtime_error("Given endpoint contains zero remote addr");
	}
}

void	UdpSocket::recvFrom(UdpBuffer &buffer, UdpEndpoint const &ep) {
	if (ep._ai.size() > 0) {
		auto		*curAddr = reinterpret_cast<sockaddr_in*>(ep._ai[0].get());
		socklen_t	len = sizeof(*curAddr);

		::recvfrom(_sock, buffer.buf, buffer.len, 0, (sockaddr*)curAddr, &len);
	} else {
		throw std::runtime_error("Given endpoint contains zero remote addr");
	}
}

int		UdpSocket::setNonBlocking(bool isNonBlocking) {
	return SOCKETIOCTL(_sock, FIONBIO, &isNonBlocking);
}

/* Usage:

int main() {

	nw::UdpSocket test;

	auto res = test.sendTo({"Patate", 7}, nw::UdpEndpoint("localhost", 1337));

	char buf[1024];
	nw::UdpBuffer buffer(buf, sizeof(buf));

	test.recvFrom(buffer, res);
	std::cout << buf << std::endl;

}

*/

}