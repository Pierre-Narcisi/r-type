/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
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
<<<<<<< HEAD
=======
#include "game/component/Parallax.hpp"
#include "game/component/Types.hpp"
>>>>>>> 9039475ccc174b3acb740d82c68820a86c9655fa
#include "game/component/Firerate.hpp"
#include "game/component/AnimationRtype.hpp"

#include "game/menu/Menu.hpp"
#include "game/menu/Selection.hpp"

#include "game/system/Parallaxs.hpp"
#include "WindowsCtor.hpp"

int main() {
	initWSA(); //Need by Windows
	{
		rtype::Menu menu;

		menu.run();
	}

	{
		rtype::Selection selection;

		selection.run();
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
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitTop, 1280, 1, true);
	ID limitBottom = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitBottom, 1280/2, 720);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitBottom, 1280, 1, true);
	ID limitLeft = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitLeft, 0, 720/2);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitLeft, 1, 720, true);
	ID limitRight = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(limitRight, 1280, 720/2);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(limitRight, 1, 720, true);


	game::system::gen Gen;
	game::system::walls Walls;

	ID background = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Parallax>(background, "assets/space.png", 100.f);

	ID ship = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Firerate>(ship, 100);
	ecs::Ecs::addComponent<ecs::component::Position>(ship, 1280/2, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(ship);
	ecs::Ecs::addComponent<game::component::Type>(ship, game::component::Type::Types::SHIP);
	ecs::Ecs::addComponent<ecs::component::Drawable>(ship, 0, true);
	ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(ship, 500.f);
	ecs::Ecs::addComponent<ecs::component::Sprite>(ship, "assets/Sprite/Ship/BlueShip/BlueShip3.png", ecs::core::Vector2<float>(64, 32));
	ecs::Ecs::addComponent<ecs::component::Hitbox>(ship, ship, true, false);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(ship);


	auto &keymap = ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[ship].keyMap;
	keymap[KeyKeyboard::ESCAPE] = std::pair<bool, std::function<void(ID)>>(false, [&rtype](ID parent) {rtype._window->close();});
	keymap[KeyKeyboard::SPACE] = std::pair<bool, std::function<void(ID)>>(false, [](ID parent) {
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire).count() > ecs::Ecs::getComponentMap<game::Firerate>()[parent]._firerate)
		{
			TimedEventAdmin m;
			ID bullet = ecs::entity::Entity::getId();
			ecs::Ecs::addComponent<ecs::component::Speed>(bullet, 10, 0);
			ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 1, true);
			ecs::Ecs::addComponent<game::component::Type>(bullet, game::component::Type::Types::BULLET_SHIP);
			ecs::Ecs::addComponent<ecs::component::Position>(bullet, ecs::Ecs::getComponentMap<ecs::component::Position>()[parent].x + 100, ecs::Ecs::getComponentMap<ecs::component::Position>()[parent].y);
			ecs::Ecs::addComponent<ecs::component::Sprite>(bullet, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["assets/Sprite/ClassicBullet/ClassicBullet3.png"], "assets/Sprite/ClassicBullet/ClassicBullet3.png");
			ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, bullet, false, [parent](ID self, ID other){
				game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
			if (type._type == game::component::Type::Types::BULLET_ENEMY || type._type == game::component::Type::Types::ENEMY) {
				TimedEventAdmin t;
				ID explosion = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
				ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
				ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/Explosion", 12, ecs::core::Vector2<float>(70,70));
               	ecs::Ecs::deleteId(other);
               	ecs::Ecs::deleteId(self);
				t.addEvent(500, Time::MilliSeconds, [explosion](){ecs::Ecs::deleteId(explosion);});
			}
        		});
			m.addEvent(2, Time::Seconds, [bullet](){ecs::Ecs::deleteId(bullet);});
			ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire = std::chrono::system_clock::now();
		}
		//hidden::ListComponent<ecs::component::Keyboard>::get().getComponentMap().erase(parent);
	});

	auto &game = ecs::Ecs::get();

	game.addUpdate(100, [&rtype](){rtype.update();});
	game.addUpdate(1, &game::Parallaxs::UpdateParallaxs);
	game.addUpdate(10, &ecs::system::Controls::UpdateDeplacement);
	game.addUpdate(10, &ecs::system::Speeds::UpdateSpeeds);
	game.addUpdate(9, &game::system::ai::updateAi);
	game.addUpdate(8, [&Walls](){Walls.updateWalls();});
	game.addUpdate(9, [&Gen](){Gen.updateGen();});

	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		game.update();

		//std::cout << ecs::Ecs::get()._deleteIds.size() << std::endl;

		auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}

	closeWSA();
}

