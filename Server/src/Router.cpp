/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Router.cpp
*/

#include <ctype.h>
#include "Router.hpp"

namespace rtype {

void	Router::resolve(std::istringstream &path, json::Entity &req, json::Entity &rep) {
	std::function<void()> next;
	
	/*
	**	Middleware execution, each middleware functions call next() recusively
	**		-> if next() isn't called, the request is aborted and req is send to the client.
	*/
	auto fct = _middlewares.begin();
	next = [&] () {
		if (fct == _middlewares.end()) return;
		(*fct)(req, rep, next);
		fct++;
	};
	next();

	std::string p;
	getline(path, p, '/');

	auto job = _sub.find(p);
	if (job == _sub.end()) {
		rep["error"] = json::makeObject {
			{"message", "Route unknown"}
		};
	} else {
		if (job->second.type == SubEntity::ENDROUTE) {
			job->second.endRoute(req, rep); // execute target command
		} else {
			job->second.subRouter->resolve(path, req, rep); // pass to the sub router
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
