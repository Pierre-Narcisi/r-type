/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.cpp
*/

#include <iostream>
#include "ClientConnection.hpp"

namespace rtype {

ClientConnection::ClientConnection(int socketFd, nw::TcpListenerSlave::NativeAddr const &addr):
		TcpListenerSlave(socketFd, addr) {}

void	ClientConnection::onDataAvailable(std::size_t available) {
	auto data = (char*) ::operator new(available + 1);
	_sock.read(data, available);
	data[available] = 0;
	std::cout << available << ": " << data << std::endl;

	delete data;
}

}