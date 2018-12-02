/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** UdpSocket.cpp
*/

#include <memory>
#include "UdpSocket.hpp"
#include "Network/TcpSocket/TcpSocket.hpp"

#include <iostream>
namespace nw {

UdpSocket::~UdpSocket() {
	SOCKETCLOSE(_sock);
}

UdpEndpoint	UdpSocket::sendTo(UdpBuffer const &buffer, UdpEndpoint const &ep) {
	std::lock_guard<std::mutex>	_guard(_udpMutex);
	if (ep._ai.size() > 0) {
		auto		*curAddr = reinterpret_cast<sockaddr_in*>(ep._ai[0].get());
		auto		newAddr = *curAddr;
		
		if (!_isListener)
			newAddr.sin_port = ep._port;

		::sendto(_sock, buffer.buf, (SOCK_BUFFER_LEN_TYPE)buffer.len, 0, (const sockaddr*)&newAddr, sizeof(newAddr));
		return (newAddr);
	} else {
		throw std::runtime_error("Given endpoint contains zero remote addr");
	}
}

long	UdpSocket::recvFrom(UdpBuffer &buffer, UdpEndpoint &ep) {
	if (_isListener) {
		if (ep._ai.size() == 0) {
			ep._ai.emplace_back(reinterpret_cast<sockaddr*>(new sockaddr_in{0}));
		}
	}
	if (ep._ai.size() > 0) {
		std::lock_guard<std::mutex>	_guard(_udpMutex);
		auto		*curAddr = reinterpret_cast<sockaddr_in*>(ep._ai[0].get());
		socklen_t	len = sizeof(*curAddr);

		auto res = ::recvfrom(_sock, buffer.buf, (SOCK_BUFFER_LEN_TYPE)buffer.len, 0, (sockaddr*)curAddr, &len);
		if (res >= 0)
			buffer.len = res;
		return res;
	} else {
		throw std::runtime_error("Given endpoint contains zero remote addr");
	}
}

int		UdpSocket::setNonBlocking(bool isNonBlocking) {
	return SOCKETIOCTL(_sock, FIONBIO, &isNonBlocking);
}

std::uint16_t	UdpSocket::makeMeAsListener(std::uint16_t port) {
	sockaddr_in	sin = { 0 };
	socklen_t	len = sizeof(sin);

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);

	if(bind(_sock, reinterpret_cast<sockaddr*>(&sin), len) != 0) {
		std::cout << TcpSocket::getLastNetError() << std::endl;
		throw std::runtime_error(TcpSocket::getLastNetError());
	}
	getsockname(_sock, reinterpret_cast<sockaddr*>(&sin), &len);
	_isListener = true;
	return (ntohs(sin.sin_port));
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

Server:

int main() {
	nw::UdpSocket test;

	test.makeMeAsListener(1338);

	char buf[1024];
	nw::UdpBuffer buffer(buf, sizeof(buf));

	test.setNonBlocking(true);
	nw::UdpEndpoint ep;

	while (true) {
		auto c = test.recvFrom(buffer, ep);
		std::cout << "len: " << c << std::endl;
		if (c > -1) {
			buf[c] = 0;
			std::cout << ep.getResolvedIps().front() << ": " << buf << std::endl;

			test.sendTo(buffer, ep);
			break;
		}
		std::cout << "loop" << std::endl;
		//usleep(1000000);
	}
}

*/

}