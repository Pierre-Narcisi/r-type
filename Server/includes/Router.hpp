/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Router.hpp
*/


#if !defined(_ROUTER_HPP)
#define _ROUTER_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include "Json/Entity.hpp"

namespace rtype {

class Router {
public:
	using MiddlewareFct = std::function<void(json::Entity &req, json::Entity &res, std::function<void()> &next)>;
	using RouteEndFct = std::function<void(json::Entity &req, json::Entity &res)>;
private:
	struct SubEntity {
		SubEntity(RouteEndFct &&endRoute_): type(ENDROUTE), endRoute(endRoute_) {}
		SubEntity(std::shared_ptr<Router> &&subRouter_): type(SUBROUTER), subRouter(subRouter_) {}

		enum {
			ENDROUTE,
			SUBROUTER
		}	type;
		std::shared_ptr<Router>	subRouter;
		RouteEndFct 			endRoute;
	};
public:
	Router() = default;

	void	use(MiddlewareFct &&middleware) { _middlewares.push_back(middleware); }
	void	use(std::string &&path, std::shared_ptr<Router> &router) { _sub.insert(std::make_pair(path, router)); }
	void	use(std::string &&path, RouteEndFct &&endr) { _sub.insert(std::make_pair(path, endr)); }

	void	resolve(std::istream &path, json::Entity &req, json::Entity &res);

	static bool	pathIsValid(std::string const &path);
private:
	std::vector<MiddlewareFct>
		_middlewares;
	std::unordered_map<std::string, SubEntity>
		_sub;
};

}

#endif // _ROUTER_HPP
