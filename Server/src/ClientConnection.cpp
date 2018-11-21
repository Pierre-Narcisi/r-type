/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.cpp
*/

#include <iostream>
#include "ClientConnection.hpp"

namespace rtype {

ClientConnection::ClientConnection(int socketFd, nw::TcpListenerSalve::NativeAddr const &addr):
		TcpListenerSalve(socketFd, addr) {}

void	ClientConnection::onDataAvailable() {
	std::cout << "!Ah" << std::endl;
}

}