/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Server.hpp
*/

#if !defined(_SERVER_HPP)
#define _SERVER_HPP

#include <functional>
#include "Opts/Opts.hpp"
#include "TcpListener.hpp"
#include "ClientConnection.hpp"
#include "Session/Manager.hpp"

namespace rtype {

class Server {
public:
	static Server &instance() {
		static auto *srv = new Server();

		return *srv;
	}

	static void	cleanUpInstance() {
		delete &Server::instance();
	}

	int	init(int ac, char **av);
	
	void	start();
	void	stop();
	bool	isConnected(std::string const username);

	auto	&getSessionManager() { return _sessionManager; }
private:
	Server() = default;
	void	_initSignalCatch();

	std::unique_ptr<nw::TcpListener<ClientConnection>>
							_listener;
	std::function<void()>	_stop;
	common::Opts			_opts;
	session::Manager		_sessionManager;
};

}


#endif // _SERVER_HPP
