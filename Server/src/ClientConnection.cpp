/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.cpp
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include "ClientConnection.hpp"
#include "Server.hpp"
#include "Constant.hpp"

namespace rtype {

inline void ClientConnection::_sendJson(json::Entity const &resp) {
	std::ostringstream	strm;

	resp.print(strm, json::Entity::MINIFIED);
	auto resultStr = strm.str();
	_sock.write(resultStr.c_str(), resultStr.size());
}

ClientConnection::ClientConnection(int socketFd, nw::TcpListenerSlave::NativeAddr const &addr):
		TcpListenerSlave(socketFd, addr),
		JsonBuilder(_sock) {
	_onIllegalJson = [this] (json::Parser::ParserException const &e) {
		std::cout << e.what() << std::endl;

		_sendJson(json::makeObject {
			{ "error", json::makeObject {
				{ "message", e.what() }
			}}
		});
	};

	_routerInit();
	_sendJson(json::makeObject {
		{ "message", "Welcome to the r-type server!" },
		{ "sessionsPort", (int) Server::instance().getSessionManager().getListeningPort() }
	});
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


static int _playerIdCounter = 0;
void	ClientConnection::_login(json::Entity &req, json::Entity &resp) {
	if (!req["username"].isString()) {
		resp = json::makeObject {
			{"error", json::makeObject {
				{"message", "ill-formed request: username is not a string"}
			}},
			{ "status", false }
		};
		return;
	}

	std::string	username(req["username"].to<std::string>());
	if (!Server::instance().isConnected(username)) {
		this->_status.username = username;
		this->_status.logged = true;
		resp["status"] = true;
		resp["id"] = ++_playerIdCounter;
	} else {
		resp = json::makeObject {
			{"error", json::makeObject {
				{"message", "Username already in use"}
			}},
			{ "status", false }
		};
	}
}

void	ClientConnection::_routerInit() {
	namespace pl = std::placeholders;
	std::shared_ptr<Router>	sessionRouter(new Router());
	
	sessionRouter->use([this] (json::Entity &req, json::Entity &resp, std::function<void()> &next) {
		if (this->_status.logged) {
			next();
		} else {
			resp["error"] = json::makeObject {
				{ "message", "Not logged in" }
			};
			resp["status"] = false;
		}
	});

	sessionRouter->use("create", std::bind(&Server::createSession, &Server::instance(), this, pl::_1, pl::_2));
	sessionRouter->use("list", std::bind(&Server::listSessions, &Server::instance(), pl::_1, pl::_2));
	sessionRouter->use("join", std::bind(&Server::joinSession, &Server::instance(), this, pl::_1, pl::_2));
	sessionRouter->use("quit", std::bind(&Server::quitSession, &Server::instance(), this, pl::_1, pl::_2));

	_router.use("login", std::bind(&ClientConnection::_login, this, pl::_1, pl::_2));
	_router.use("session", sessionRouter);
}

}