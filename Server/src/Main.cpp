/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Main.cpp
*/

#include <iostream>
#include "Server.hpp"

int main(int ac, char **av) {
	auto	s = rtype::Server::instance();

	if (s.init(ac, av)) {
		return (0);
	}
#ifdef NDEBUG
	try {
#endif
		s.start();
#ifdef NDEBUG
	} catch (std::exception &s) {
		std::cout << s.what() << std::endl;
		return (84);
	}
#endif
	return (0);
}