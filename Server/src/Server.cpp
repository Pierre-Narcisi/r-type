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
#include "TcpListener.hpp"
#include "ClientConnection.hpp"

namespace rtype {

void	Server::_initSignalCatch() {
	static auto handler = [] (int sig) {
		auto &s = Server::instance();

		s.stop();
	};
	void (*handlerPtr)(int) = handler;

	signal(SIGINT, handler);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	signal(SIGQUIT, handler);
}

int	Server::init(int ac, char **av) {
	_initSignalCatch();

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
	nw::TcpListener<ClientConnection>	listener(
		static_cast<std::uint32_t>(opts["port"]->as<common::Opts::Int>())
	);

	_stop = [&listener] { listener.stop(); };

	listener.onNewConnection = [this] (ClientConnection &slave) {
		auto &addr = reinterpret_cast<const sockaddr&>(slave.getNativeAddr());

		std::cout << "New connection form " << nw::TcpEndpoint::getIp(addr) << std::endl;
	};

	listener.init();
	listener.run();
}

void	Server::stop() {
	if (_stop) _stop();
}

}