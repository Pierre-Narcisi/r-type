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

inline void ClientConnection::_sendJson(json::Entity const &rep) {
	std::ostringstream	strm;

	rep.print(strm, json::Entity::MINIFIED);
	auto resultStr = strm.str();
	_sock.write(resultStr.c_str(), resultStr.size());
}

ClientConnection::ClientConnection(int socketFd, nw::TcpListenerSlave::NativeAddr const &addr):
		TcpListenerSlave(socketFd, addr),
		JsonBuider(_sock) {
	_onIllegalJson = [this] (json::Parser::ParserException const &e) {
		std::cout << e.what() << std::endl;

		_sendJson(json::makeObject {
			{ "error", json::makeObject {
				{ "message", e.what() }
			}}
		});
	};

	_routerInit();
}

void	ClientConnection::onDataAvailable(std::size_t available) {
	auto commands = _extractJsonObjects(available);

	for (auto &cmd: commands) {
		json::Entity	rep(json::Entity::OBJ);
		std::string		path;

		if (cmd.isObject() && cmd["path"].isString() &&
		Router::pathIsValid((path = cmd["path"].to<std::string>()))) {
			std::istringstream	stm(path);

			_router.resolve(stm, cmd, rep);
		} else {
			rep = json::makeObject {
				{"error", json::makeObject {
					{"message", "ill-formed request ex: { \"path\": \"This:is:a:path\" }"}
				}}
			};
		}

		_sendJson(rep);
	}
}

void	ClientConnection::_login(json::Entity &req, json::Entity &res) {

}

void	ClientConnection::_routerInit() {
	std::shared_ptr<Router>	sessionRouter(new Router());

	_router.use("login", [this] (json::Entity &req, json::Entity &rep) {
		this->_login(req, rep);
	});
	_router.use("session", sessionRouter);
}

}