/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.cpp
*/

#include <iostream>
#include "Session/Session.hpp"
#include "Session/Game.hpp"

namespace rtype { namespace session {

void	Game::init() {
	_ecs = &ecs::Ecs::get();
	//init all Components

	auto	comp1 = ecs::entity::Entity::getId();
	//Do something

	proto::Create	pack{proto::Type::CREATE, _parent->_id, 0, comp1, 50, 50, 1};
	_parent->sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
}

void	Game::_initSystems() {
	//init all systems
}

void	Game::update() {
	_ecs->update();
}

void	Game::onKeyPress(int internPlayerId, ID playerId, proto::KeyPress &packet) {

	std::cout << "Press " << packet.keyCode << std::endl;
}

void	Game::onKeyRelease(int internPlayerId, ID playerId, proto::KeyRelease &packet) {
	std::cout << "Press " << packet.keyCode << std::endl;
}

}}