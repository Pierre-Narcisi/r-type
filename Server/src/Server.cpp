/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Server.cpp
*/

#include <iostream>
#include "Constant.hpp"
#include "Server.hpp"

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
		"test : " << opts["test"]->as<common::Opts::String>() << std::endl <<
		"f : " << opts['f']->as<common::Opts::Float>() << std::endl;
}

void	Server::start() {
	
}

}