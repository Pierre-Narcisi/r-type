/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Server.cpp
*/

#include <iostream>
#include "Constant.hpp"
#include "Server.hpp"
#include "TcpListener.hpp"

namespace rtype {

int	Server::init(int ac, char **av) {
	opts.setArgs(ac, av);

	opts.setUsage("Usage", std::string(av[0]) + " [-p port]");
	opts.setArgsTitle("Available Arguments");
	opts.setOptions({
		{"help", 'h', common::Opts::noArg(), "Show this help"},
		{"host", 'i', common::Opts::makeString(constant::defHost), "Server host address"},
		{"port", 'p', common::Opts::makeInt(constant::defPort), "Server listening port"}
	});

	opts.parse();
	if (opts["help"]->count()) {
		std::cout << opts << std::endl;
		return -1;
	}

	std::cout <<
		"port : " << opts["port"]->as<common::Opts::Int>() << std::endl <<
		"host : " << opts["host"]->as<common::Opts::String>() << std::endl;
	return (0);
}

void	Server::start() {
	nw::TcpListener<nw::TcpListenerSalve>	listener(opts["port"]->as<common::Opts::Int>());

	listener.onNewConnection = [this] (nw::TcpListenerSalve &slave) {
		std::cout << "New connection!" << std::endl;
	};

	listener.onDataAvailable = [this] (nw::TcpListenerSalve &slave) {
		std::cout << "New data at: " << slave.getNativeSocket() << "!" << std::endl;
	};

	listener.init();
	std::cout << "Hummmm ??" << std::endl;
	listener.run();
}

}