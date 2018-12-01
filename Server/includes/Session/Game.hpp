/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.hpp
*/

#if !defined(_RTYPE_SERVER_GAME_HPP)
#define _RTYPE_SERVER_GAME_HPP

#include <list>
#include "GameEngine/ecs/Ecs.hpp"
#include "GameEngine/component/control/Keyboard.hpp"
#include "Network/GameProtocol.hpp"
#include "Session.hpp"

namespace rtype { namespace session {

class Manager;

class	Game {
public:
	Game(Session &parent): _parent(&parent), _ecs(nullptr) {}

	void	init();

	void	update();

	void	onKeyPress(int internPlayerId, ID playerId, proto::KeyPress&);
	void	onKeyRelease(int internPlayerId, ID playerId, proto::KeyRelease&);

	auto	&getEcs() { return *_ecs; }
private:
	void	_initSystems();

	Session		*_parent;
	ecs::Ecs	*_ecs;
	std::list<ID>	_collector;


	// friend Manager;
	// friend Session;
};

}}

#endif // _RTYPE_SERVER_GAME_HPP
