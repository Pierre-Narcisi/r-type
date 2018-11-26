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

void	Server::stop() {
	if (_stop) _stop();
}

}