/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.cpp
*/

#include <iostream>
#include <sstream>
#include "ClientConnection.hpp"

namespace rtype {

ClientConnection::ClientConnection(int socketFd, nw::TcpListenerSlave::NativeAddr const &addr):
		TcpListenerSlave(socketFd, addr),
		JsonBuider(_sock) {
	_onIllegalJson = [] (json::Parser::ParserException const &e) {
		std::cout << e.what() << std::endl;
	};
}

void	ClientConnection::onDataAvailable(std::size_t available) {
	auto commands = _extractJsonObjects(available);

	for (auto &cmd: commands) {
		// TODO: interpret command
		std::cout << cmd << std::endl;
	}
}

}