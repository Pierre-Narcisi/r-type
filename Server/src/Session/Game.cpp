/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.cpp
*/

#define NOSPRITE
#include <iostream>
#include "Server/src/Session/systems/walls.hpp"
#include "system/physic/Speeds.hpp"
#include "component/physic/Position.hpp"
#include "component/online/OnlineComponent.hpp"
#include "component/physic/Hitbox.hpp"
#include "system/control/Controls.hpp"
#include "Session/Session.hpp"
#include "Session/systems/gen.hpp"
#include "Session/systems/ai.hpp"
#include "Session/systems/Bonuses.hpp"
#include "Session/Game.hpp"
#undef NOSPRITE

namespace rtype { namespace session {

void	Game::init() {
	_ecs = &ecs::Ecs::get();
	//init all Components

	std::shared_ptr<game::system::gen>		gen(new game::system::gen());
	std::shared_ptr<game::system::walls>	walls(new game::system::walls());

	ID limitTop = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Speed>(limitTop, 0, 0);
	ecs::Ecs::addComponent<ecs::component::Position>(limitTop, 1280/2, 0);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitTop, 1280.f, 1.f, true);
	ID limitBottom = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Speed>(limitTop, 0, 0);
	ecs::Ecs::addComponent<ecs::component::Position>(limitBottom, 1280/2, 720);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitBottom, 1280.f, 1.f, true);
	ID limitLeft = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Speed>(limitTop, 0, 0);
	ecs::Ecs::addComponent<ecs::component::Position>(limitLeft, 0, 720/2);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitLeft, 1.f, 720.f, true);
	ID limitRight = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Speed>(limitTop, 0, 0);
	ecs::Ecs::addComponent<ecs::component::Position>(limitRight, 1280, 720/2);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitRight, 1.f, 720.f, true);

	_ecs->addUpdate(10, &ecs::system::Controls::UpdateDeplacement);
	_ecs->addUpdate(2, &ecs::system::Controls::UpdateKeyboards);
	_ecs->addUpdate(2, &ecs::system::Controls::UpdateMouses);
	_ecs->addUpdate(2, &ecs::system::Speeds::UpdateSpeeds);
	_ecs->addUpdate(8, &game::system::Bonuses::UpdateBonuses);
	_ecs->addUpdate(9, std::bind(&game::system::ai::updateAi, std::ref(*_parent)));
	_ecs->addUpdate(9, [this, gen]{
		gen->updateGen(*_parent);
	});
	_ecs->addUpdate(9, [this, walls]{
		walls->updateWalls(*_parent);
	});
	_ecs->addUpdate(15, [this] () {
		auto ids = ecs::Ecs::filter<ecs::component::Position>();
		auto pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		for (auto id : ids) {
			proto::Move	buf{proto::Type::MOVE, _parent->_id, 0, id, pos[id].x, pos[id].y };
			_parent->sendToPlayers(reinterpret_cast<proto::PacketBase&>(buf), sizeof(buf));
		}
	});

	auto ids = ecs::Ecs::filter<ecs::component::Position, ecs::component::Hitbox, ecs::component::OnlineComponent>();
	auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
	auto &hitbox = ecs::Ecs::getComponentMap<ecs::component::Hitbox>();
	auto &online = ecs::Ecs::getComponentMap<ecs::component::OnlineComponent>();
	for (auto id: ids) {
		proto::Create	pack{
			proto::Type::CREATE, _parent->_id, 0, id,
			hitbox[id].width, hitbox[id].height,
			pos[id].x, pos[id].y,
			online[id].spriteId
		};

		_parent->sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
	}
}

void	Game::_initSystems() {
	//init all systems
}

void	Game::update() {
	_ecs->update();
}

void	Game::onKeyPress(int internPlayerId, ID playerId, proto::KeyPress &packet) {
	ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[playerId].keyMap[static_cast<KeyKeyboard>(packet.keyCode)].first = true;
}

void	Game::onKeyRelease(int internPlayerId, ID playerId, proto::KeyRelease &packet) {
	ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[playerId].keyMap[static_cast<KeyKeyboard>(packet.keyCode)].first = false;
}

}}