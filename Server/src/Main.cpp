/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Main.cpp
*/

#include <iostream>
#include "Server.hpp"

int main(int ac, char **av) {
	auto	&s = rtype::Server::instance();

	if (s.init(ac, av)) {
		rtype::Server::cleanUpInstance();
		return (0);
	}
#ifdef NDEBUG
	try {
#endif
		s.start();
#ifdef NDEBUG
	} catch (std::exception &s) {
		std::cerr << s.what() << std::endl;
		rtype::Server::cleanUpInstance();
		return (84);
	}
#endif
	rtype::Server::cleanUpInstance();
	return (0);
}