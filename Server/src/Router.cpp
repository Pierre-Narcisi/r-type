/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Router.cpp
*/

#include <ctype.h>
#include "Router.hpp"

#include <iostream>

namespace rtype {

void	Router::resolve(std::istream &path, json::Entity &req, json::Entity &resp) {
	std::function<void()> next;
	
	/*
	**	Middleware execution, each middleware functions call next() recusively
	**		-> if next() isn't called, the request is aborted and req is send to the client.
	*/
	auto fct = _middlewares.begin();
	next = [&] () {
		if (fct == _middlewares.end()) return;

		decltype(next)	ovNext = [&] () {
			fct++;
			next();
		};
		(*fct)(req, resp, ovNext);
	};
	next();

	if (fct != _middlewares.end())
		return;

	std::string p("");
	auto &stm = getline(path, p, ':');

	for (auto &tmp: _sub) {
		std::cout << '"' << tmp.first << '"'
			<< " ? == ? " << '"' << p << '"' << std::endl;
	}
	auto job = _sub.find(p);
	if (job == _sub.end()) {
		resp["error"] = json::makeObject {
			{"message", "Route unknown"}
		};
	} else {
		if (job->second.type == SubEntity::ENDROUTE) {
			job->second.endRoute(req, resp); // execute target command
		} else {
			job->second.subRouter->resolve(stm, req, resp); // pass to the sub router
		}
	}
}

bool	Router::pathIsValid(std::string const &path) {
	for (auto c: path) {
		if (!(::isalnum(c) || c == ':'))
			return false;
	}
	return true;
}

}
