/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Server.hpp
*/

#if !defined(_SERVER_HPP)
#define _SERVER_HPP

#include "Opts/Opts.hpp"

namespace rtype {

class Server {
public:
	static Server &instance() {
		static auto srv = new Server();

		return *srv;
	}

	int	init(int ac, char **av);
	
	void start();
private:
	Server() = default;

	common::Opts	opts;
};

}


#endif // _SERVER_HPP
