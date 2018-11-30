/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.hpp
*/

#include <list>
#include "GameEngine/ecs/Ecs.hpp"
#include "GameEngine/component/control/Keyboard.hpp"
#include "Network/GameProtocol.hpp"

#if !defined(_RTYPE_SERVER_GAME_HPP)
#define _RTYPE_SERVER_GAME_HPP

namespace rtype { namespace session {

class Manager;
class Session;

class	Game {
public:
	Game(): _ecs(nullptr) {}
	
	void	init();

	void	update();

	void	onKeyPress(ID player, proto::KeyPress&);
	void	onKeyRelease(ID player, proto::KeyRelease&);
private:
	void	_initSystems();
	
	ecs::Ecs		*_ecs;
	std::list<ID>	_collector;

	// friend Manager;
	// friend Session;
};

}}

#endif // _RTYPE_SERVER_GAME_HPP
