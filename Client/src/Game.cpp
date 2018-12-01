/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Game.cpp
*/

#include "component/ai.hpp"
#include "system/gen.hpp"
#include "enemy/enemy1/enemy1.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include "game/system/walls.hpp"
#include "system/ai.hpp"
#include <zconf.h>
#include <ecs/Entity.hpp>
#include <ecs/Ecs.hpp>
#include <component/graphical/Sprite.hpp>
#include <system/graphical/Graphicals.hpp>
#include <component/physic/Position.hpp>
#include <component/control/DeplacementKeyBoard.hpp>
#include <component/control/Keyboard.hpp>
#include <component/physic/Speed.hpp>
#include <system/physic/Speeds.hpp>
#include <component/physic/Hitbox.hpp>
#include <component/graphical/AnimatedSprite.hpp>
#include <component/graphical/AnimatedSpriteMap.hpp>
#include <component/graphical/Drawable.hpp>
#include <ecs/DataBank.hpp>
#include <component/audio/Sound.hpp>
#include <component/control/DeplacementMouse.hpp>
#include "sfml/Graphic.hpp"
#include "core/Time.hpp"
#include "../lib/TimedEvent/TimedEventAdmin.hpp"
#include "game/component/Parallax.hpp"
#include "game/component/Firerate.hpp"
#include "game/component/AnimationRtype.hpp"
#include "game/system/Parallaxs.hpp"

#include "game/menu/Menu.hpp"
#include "game/menu/Selection.hpp"

#include "game/system/Fire.hpp"
#include "component/Bonuses.hpp"
#include "system/Bonuses.hpp"

#include "Game.hpp"

namespace rtype {

void	Game::start(ServerConnection &srv) {
	{
		rtype::Menu menu;

		menu.run(srv);
	}

	auto createRes = srv.makeSession("session1", 8);
	if (createRes["status"] == false) {
		rtype::MsgBox::show("Session create failed", "(!) " + createRes["error"]["message"].to<std::string>());
	}

	{
		rtype::Selection selection;

		selection.run(std::bind(&ServerConnection::getSessions, &srv));
	}

	std::srand(std::time(nullptr));
	auto &rtype = ecs::graphical::Graphic::get();
	ecs::DataBank<std::string, sf::SoundBuffer>::get().creator = [](std::string path){
		sf::SoundBuffer buffer;
		buffer.loadFromFile(path);
		return buffer;
	};
	ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get().creator = [](std::string path){
		ecs::graphical::BundleSprite buffer;
		buffer.texture = new sf::Texture();
		buffer.texture->loadFromFile(path);
		buffer.sprite = new sf::Sprite(*buffer.texture);
		return buffer;
	};

	ID limitTop = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitTop, 1280/2, 0);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitTop, 1280.f, 1.f, true);
	ID limitBottom = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitBottom, 1280/2, 720);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitBottom, 1280.f, 1.f, true);
	ID limitLeft = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitLeft, 0, 720/2);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitLeft, 1.f, 720.f, true);
	ID limitRight = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitRight, 1280, 720/2);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitRight, 1.f, 720.f, true);

	game::system::gen Gen;
	game::system::walls Walls;

	ID background = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Parallax>(background, "assets/space.png", 100.f);

	ID ship = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Firerate>(ship, 100);
	ecs::Ecs::addComponent<ecs::component::Position>(ship, 1280/2, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(ship);
	ecs::Ecs::addComponent<game::component::Inventory>(ship);
	ecs::Ecs::addComponent<game::component::Type>(ship, game::component::Type::Types::SHIP);
	ecs::Ecs::addComponent<ecs::component::Drawable>(ship, 0, true);
	ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(ship, 500.f);
	ecs::Ecs::addComponent<ecs::component::Sprite>(ship, "assets/Sprite/Ship/BlueShip/BlueShip3.png", ecs::core::Vector2<float>(64, 32));
	ecs::Ecs::addComponent<ecs::component::Hitbox>(ship, ship, true, false);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(ship);

	auto &keymap = ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[ship].keyMap;
	keymap[KeyKeyboard::ESCAPE] = std::pair<bool, std::function<void(ID)>>(false, [&rtype](ID parent) {rtype._window->close();});
	keymap[KeyKeyboard::SPACE] = std::pair<bool, std::function<void(ID)>>(false, &game::system::Fire::shoot);
	
	auto &game = ecs::Ecs::get();

	game.addUpdate(100, [&rtype](){rtype.update();});
	game.addUpdate(1, &game::Parallaxs::UpdateParallaxs);
	game.addUpdate(10, &ecs::system::Controls::UpdateDeplacement);
	game.addUpdate(10, &ecs::system::Speeds::UpdateSpeeds);
	game.addUpdate(9, &game::system::ai::updateAi);
	game.addUpdate(8, &game::system::Bonuses::UpdateBonuses);
	game.addUpdate(8, [&Walls](){Walls.updateWalls();});
	game.addUpdate(9, [&Gen](){Gen.updateGen();});

	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		auto list = srv.getAvailablePackets();

		for (auto &packet: list) {
			switch (packet->type) {
				case (proto::Type::MOVE):
					_onReceiveMove(reinterpret_cast<proto::Move&>(*packet));
					break;
				case (proto::Type::CREATE):
					_onReceiveCreate(reinterpret_cast<proto::Create&>(*packet));
					break;
				case (proto::Type::DELETE):
					_onReceiveDelete(reinterpret_cast<proto::Delete&>(*packet));
					break;
				default: break;
			}
		}

		game.update();

		//std::cout << ecs::Ecs::get()._deleteIds.size() << std::endl;

		auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}
}

void	Game::_onReceiveMove(proto::Move &packet) {
	//Do something;
}

void	Game::_onReceiveCreate(proto::Create &packet) {
	//Do something;
}

void	Game::_onReceiveDelete(proto::Delete &packet) {
	//Do something;
}

}