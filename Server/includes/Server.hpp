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
private:
	Server() = default;
	void	_initSignalCatch();

	std::function<void()>	_stop;
	common::Opts			opts;
};

}


#endif // _SERVER_HPP
