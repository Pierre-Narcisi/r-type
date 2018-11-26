/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <zconf.h>
#include "game_engine/ecs/Entity.hpp"
#include "game_engine/ecs/Ecs.hpp"
#include "game_engine/component/graphical/Sprite.hpp"
#include "game_engine/system/graphical/Graphicals.hpp"
#include "game_engine/component/physic/Position.hpp"
#include "game_engine/component/control/DeplacementKeyBoard.hpp"
#include "game_engine/component/control/Keyboard.hpp"
#include "game_engine/component/physic/Speed.hpp"
#include "game_engine/system/physic/Speeds.hpp"
#include "game_engine/component/physic/Hitbox.hpp"
#include "game_engine/component/graphical/AnimatedSprite.hpp"
#include "game_engine/component/graphical/AnimatedSpriteMap.hpp"
#include "game_engine/component/graphical/Drawable.hpp"
#include "game_engine/ecs/DataBank.hpp"
#include "game_engine/component/audio/Sound.hpp"
#include "game_engine/component/control/DeplacementMouse.hpp"
#include "game_engine/sfml/Graphic.hpp"
#include "game_engine/core/Time.hpp"
#include "../lib/TimedEvent/TimedEventAdmin.hpp"
#include "game/component/Parallax.hpp"
#include "game/component/Firerate.hpp"
#include "game/component/AnimationRtype.hpp"
#include "game/system/Parallaxs.hpp"
#include "game_engine/component/physic/Speed.hpp"

int main() {
	auto &rtype = ecs::graphical::Graphic::get();
	ecs::DataBank<std::string, sf::SoundBuffer>::get().creator = [](std::string path){
		sf::SoundBuffer buffer;
		buffer.loadFromFile(path);
		return buffer;
	};

	ID background = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Parallax>(background, "assets/space.png", 100.f);

	ID ship = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Firerate>(ship, 100);
	ecs::Ecs::addComponent<ecs::component::Position>(ship, 1280/2, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(ship, 10, 10);
	ecs::Ecs::addComponent<ecs::component::Drawable>(ship, 0, true);
	ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(ship);
	ecs::Ecs::addComponent<ecs::component::AnimatedSpriteMap>(ship, "Sprite/Ship/BlueShip");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(ship, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").x, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").y);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(ship);

	ID enemy = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(enemy, 1000, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(enemy, 0, 0);
	ecs::Ecs::addComponent<ecs::component::Drawable>(enemy, 0, true);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(enemy, ecs::graphical::Graphic::getTextureSize("Sprite/Enemy1/Enemy11.png").x, ecs::graphical::Graphic::getTextureSize("Sprite/Enemy1/Enemy11.png").y);
	ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(enemy, "Sprite/Enemy1");

	auto &keymap = ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[ship].keyMap;
	keymap[KeyKeyboard::KEY_Z] = std::pair<bool, std::function<void(ID)>>(false, [](ID self){
		//ecs::Ecs::getComponentMap<game::AnimationRtype>()[self]. = "up";
		ecs::Ecs::getComponentMap<ecs::component::AnimatedSpriteMap>()[self].pos = "up";
	});
	keymap[KeyKeyboard::KEY_S] = std::pair<bool, std::function<void(ID)>>(false, [](ID self){
		ecs::Ecs::getComponentMap<ecs::component::AnimatedSpriteMap>()[self].pos = "down";
	});
	keymap[KeyKeyboard::SPACE] = std::pair<bool, std::function<void(ID)>>(false, [](ID parent){
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() -
										  ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire).count() >
			ecs::Ecs::getComponentMap<game::Firerate>()[parent]._firerate)
		{
			TimedEventAdmin m;
			ID bullet = ecs::entity::Entity::getId();
			ecs::Ecs::addComponent<ecs::component::Speed>(bullet, 10, 0);
			ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 0, true);
			ecs::Ecs::addComponent<ecs::component::Position>(bullet,
									 ecs::Ecs::getComponentMap<ecs::component::Position>()[parent].x,
									 ecs::Ecs::getComponentMap<ecs::component::Position>()[parent].y);
			ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, ecs::graphical::Graphic::getTextureSize("Sprite/ClassicBullet/ClassicBullet3.png").x, ecs::graphical::Graphic::getTextureSize("Sprite//ClassicBullet/ClassicBullet3.png").y, true, [parent](ID self, ID other){
					if (other != parent)
					{
						TimedEventAdmin t;
						ID explosion = ecs::entity::Entity::getId();
						ecs::Ecs::addComponent<ecs::component::Speed>(explosion, 0, 0);
						ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 0, true);
						ecs::Ecs::addComponent<ecs::component::Position>(explosion,
												 ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x,
												 ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
						ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "Sprite/Explosion", 12);
                        ecs::Ecs::deleteId(other);
                        ecs::Ecs::deleteId(self);
						t.addEvent(500, Time::MilliSeconds, [explosion](){ecs::Ecs::deleteId(explosion);});
					}
        		});
			ecs::Ecs::addComponent<ecs::component::Sprite>(bullet, "Sprite/ClassicBullet/ClassicBullet3.png");
			m.addEvent(2, Time::Seconds, [bullet](){ecs::Ecs::deleteId(bullet);});
			ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire = std::chrono::system_clock::now();
		}
	});

	auto &game = ecs::Ecs::get();
	game.addUpdate(100, [&rtype](){rtype.update();});
	game.addUpdate(1, [](){game::Parallaxs::UpdateParallaxs();});
	game.addUpdate(10, [](){ecs::system::Controls::UpdateDeplacement();});
	game.addUpdate(10, [](){ecs::system::Speeds::UpdateSpeeds();});

	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);

		game.update();

		auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);

		std::cout << x << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(x));
	}

}