/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include "Opts/Opts.hpp"
#include "MessageBox.hpp"
#include "Game.hpp"
#include "ServerConnection.hpp"
#include "Constant.hpp"
#include "WindowsCtor.hpp"

inline common::Opts	getOpts(int ac, char **av) {
	common::Opts	_opts;

	_opts.setArgs(ac, av);

	_opts.setUsage("Usage", std::string(av[0]) + " [-p port]");
	_opts.setArgsTitle("Available Arguments");
	_opts.setOptions({
		{"help", 'h', common::Opts::noArg(), "Show this help"},
		{"server", 's', common::Opts::makeString(constant::defHost), "Server host address"},
		{"port", 'p', common::Opts::makeInt(constant::defPort), "Server listening port"}
	});

	_opts.parse();
	if (_opts["help"]->count()) {
		std::cout << _opts << std::endl;
		exit (0);
	}
	return _opts;
}

int main(int ac, char **av) {
	initWSA(); //Need by Windows

	auto					opts = getOpts(ac, av);
	rtype::ServerConnection	srv;
	rtype::Game				game;

	try {
		srv.connect(opts["server"]->as<common::Opts::String>(), opts["port"]->as<common::Opts::Int>());
	} catch (std::exception &e) {
		rtype::MsgBox::show("Connection ERROR", std::string("(!) ") + e.what());
		
		return (84);
	}
	auto loginRes = srv.login("ben");
	if (loginRes["status"] == false) {
		rtype::MsgBox::show("Login failed", "(!) " + loginRes["error"]["message"].to<std::string>());
		return (0); //TODO: change this !!
	}
	auto createRes = srv.makeSession("session1", 8);
	if (createRes["status"] == false) {
		rtype::MsgBox::show("Session create failed", "(!) " + createRes["error"]["message"].to<std::string>());
	}
	std::cout << srv.getSessions() << std::endl;
	
	srv.run();

	game.start(srv);

	srv.stop();

	closeWSA();
}
