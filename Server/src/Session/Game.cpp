/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.cpp
*/

#include <iostream>
#include <system/physic/Speeds.hpp>
#include <component/physic/Position.hpp>
#include "system/control/Controls.hpp"
#include "Session/Session.hpp"
#include "Session/Game.hpp"

namespace rtype { namespace session {

void	Game::init() {
	_ecs = &ecs::Ecs::get();
	//init all Components

	auto	comp1 = ecs::entity::Entity::getId();
	//Do something


	_ecs->addUpdate(10, &ecs::system::Controls::UpdateDeplacement);
	_ecs->addUpdate(2, &ecs::system::Controls::UpdateKeyboards);
	_ecs->addUpdate(2, &ecs::system::Controls::UpdateMouses);
	_ecs->addUpdate(2, &ecs::system::Speeds::UpdateSpeeds);
	_ecs->addUpdate(15, [this] () {
		auto ids = ecs::Ecs::filter<ecs::component::Position>();
		auto pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		for (auto id : ids) {
			proto::Move	buf{proto::Type::MOVE, _parent->_id, 0, id, pos[id].x, pos[id].y };
			_parent->sendToPlayers(reinterpret_cast<proto::PacketBase&>(buf), sizeof(buf));
		}
	});

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
	ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[playerId].keyMap[static_cast<KeyKeyboard>(packet.keyCode)].first = true;
}

void	Game::onKeyRelease(int internPlayerId, ID playerId, proto::KeyRelease &packet) {
	std::cout << "Release " << packet.keyCode << std::endl;
	ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[playerId].keyMap[static_cast<KeyKeyboard>(packet.keyCode)].first = false;
}

}}