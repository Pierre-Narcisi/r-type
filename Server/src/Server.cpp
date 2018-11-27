/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Server.cpp
*/

#include <signal.h>  
#include <iostream>
#include "Constant.hpp"
#include "Server.hpp"

#include "Network/UdpSocket/UdpSocket.hpp"

#define ERROR(__text) { \
	resp = json::makeObject { \
		{ "error", json::makeObject { \
			{ "message", __text } \
		}} \
	}; \
	return; \
}

namespace rtype {

void	Server::_initSignalCatch() {
	static auto handler = [] (int sig) {
		auto &s = Server::instance();

		s.stop();
	};

	signal(SIGINT, handler);
#if !defined(_MSC_VER)
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	signal(SIGQUIT, handler);
#endif
}

int	Server::init(int ac, char **av) {
	_initSignalCatch();

	_opts.setArgs(ac, av);

	_opts.setUsage("Usage", std::string(av[0]) + " [-p port]");
	_opts.setArgsTitle("Available Arguments");
	_opts.setOptions({
		{"help", 'h', common::Opts::noArg(), "Show this help"},
		{"host", 'i', common::Opts::makeString(constant::defHost), "Server host address"},
		{"port", 'p', common::Opts::makeInt(constant::defPort), "Server listening port"}
	});

	_opts.parse();
	if (_opts["help"]->count()) {
		std::cout << _opts << std::endl;
		return -1;
	}

	std::cout <<
		"port : " << _opts["port"]->as<common::Opts::Int>() << std::endl <<
		"host : " << _opts["host"]->as<common::Opts::String>() << std::endl;
	return (0);
}

void	Server::start() {
	_listener = std::unique_ptr<nw::TcpListener<ClientConnection>>(new nw::TcpListener<ClientConnection>(
		static_cast<std::uint32_t>(_opts["port"]->as<common::Opts::Int>())
	));

	_stop = [this] { _listener->stop(); };

	_listener->onNewConnection = [this] (ClientConnection &slave) {
		auto it = _listener->getSlaves().end();
		it--;
		auto &addr = reinterpret_cast<const sockaddr&>(slave.getNativeAddr());

		std::cout << "New connection form " << nw::TcpEndpoint::getIp(addr) << std::endl;
		// slave.onDestroy.addHandler([this, it] {
		// 	_listener->getSlaves().erase(it);
		// });
	};

	_listener->init();
	_listener->run();
}

bool	Server::isConnected(std::string const username) {
	if (_listener == nullptr) return false;

	auto &list = _listener->getSlaves();
	for (auto &slave: list) {
		if (slave._status.logged && slave._status.username == username) {
			return true;
		}
	}
	return false;
}

void	Server::createSession(ClientConnection *me, json::Entity &req, json::Entity &resp) {
	try {
		#if defined(_MSC_VER)
			#define __MAX max
			#define __MIN min
		#else
			#define __MAX std::max
			#define __MIN std::min
		#endif
		auto &session = Server::instance().getSessionManager().create(
			req["name"].to<std::string>(),
			__MIN(__MAX(1, req["playerMax"].to<int>()), constant::maxSessionPlayer)
		);

		session.addPlayer(*me);
		resp["status"] = true;
		resp["id"] = session.getId();
	} catch (std::exception &e) {
		resp = json::makeObject {
			{ "error", json::makeObject {
				{ "message", e.what() }
			}}
		};
	}
}

void	Server::listSessions(json::Entity &req, json::Entity &resp) {
	resp["sessions"] = json::Entity(json::Entity::ARR);
	auto &list = _sessionManager.getSessions();

	for (auto &session: list) {
		resp["sessions"].push(json::makeObject {
			{ "name", session._name },
			{ "id", session._id },
			{ "playerCount", (int) session._players.size() },
			{ "playerMax", session._playerMax }
		});
	}
	resp["status"] = true;
}

void	Server::joinSession(ClientConnection *me, json::Entity &req, json::Entity &resp) {
	if (!req["sessionId"].isNumber()) ERROR("sessionId is not a number!")
	
	auto id = (uint32_t) req["sessionId"].to<int>();
	for (auto &session: Server::instance().getSessionManager().getSessions()) {
		if (session._id == id) {
			for (auto &client: session._players) {
				if (client->_status.username == me->_status.username)
					ERROR("You are already in");
			}
			session.addPlayer(*me);
			resp["status"] = true;
			return;
		}
	}
	ERROR("sessionId: Not found");
}

void	Server::quitSession(ClientConnection *me, json::Entity &req, json::Entity &resp) {
	if (!req["sessionId"].isNumber()) ERROR("sessionId is not a number!")

	auto id = (uint32_t) req["sessionId"].to<int>();
	for (auto &session: Server::instance().getSessionManager().getSessions()) {
		if (session._id == id) {
			auto it = session._players.begin();

			for (; it != session._players.end(); ++it) {
				if ((*it)->_status.username == me->_status.username) {
					session._rmPlayer(it);
					resp["status"] = true;
					return;
				}
			}
			ERROR("You are not in");
		}
	}
	ERROR("sessionId: Not found");
}

void	Server::stop() {
	if (_stop) _stop();
}

}