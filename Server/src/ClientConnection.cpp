/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.cpp
*/

#include <iostream>
#include <sstream>
#include "ClientConnection.hpp"
#include "Server.hpp"

namespace rtype {

inline void ClientConnection::_sendJson(json::Entity const &resp) {
	std::ostringstream	strm;

	resp.print(strm, json::Entity::MINIFIED);
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
		json::Entity	resp(json::Entity::OBJ);
		std::string		path;

		if (cmd.isObject() && cmd["path"].isString() &&
		Router::pathIsValid((path = cmd["path"].to<std::string>()))) {
			std::istringstream	stm(path);

			_router.resolve(stm, cmd, resp);
		} else {
			resp = json::makeObject {
				{"error", json::makeObject {
					{"message", "ill-formed request ex: { \"path\": \"This:is:a:path\" }"}
				}}
			};
		}

		_sendJson(resp);
	}
}


void	ClientConnection::_login(json::Entity &req, json::Entity &resp) {
	if (!req["username"].isString()) {
		resp = json::makeObject {
			{"error", json::makeObject {
				{"message", "ill-formed request: username is not a string"}
			}}
		};
		return;
	}

	std::string	username(req["username"].to<std::string>());
	if (!Server::instance().isConnected(username)) {
		this->_status.username = username;
		this->_status.logged = true;
		resp["status"] = true;
	} else {
		resp = json::makeObject {
			{"error", json::makeObject {
				{"message", "Username already in use"}
			}}
		};
	}
}

void	ClientConnection::_routerInit() {
	std::shared_ptr<Router>	sessionRouter(new Router());
	
	sessionRouter->use([this] (json::Entity &req, json::Entity &resp, std::function<void()> &next) {
		if (this->_status.logged) {
			next();
		} else {
			resp["error"] = json::makeObject {
				{ "message", "Not logged in" }
			};
		}
	});

	sessionRouter->use("create", [this] (json::Entity &req, json::Entity &resp) {
		resp["status"] = "created";
	});

	_router.use("login", [this] (json::Entity &req, json::Entity &resp) {
		this->_login(req, resp);
	});
	_router.use("session", sessionRouter);
}

}