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

int main() {
	auto &rtype = ecs::graphical::Graphic::get();
	ecs::DataBank<std::string, sf::SoundBuffer>::get().creator = [](std::string path){
		sf::SoundBuffer buffer;
		buffer.loadFromFile(path);
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


	ID background = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Parallax>(background, "assets/space.png", 100.f);

	ID ship = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Firerate>(ship, 100);
	ecs::Ecs::addComponent<ecs::component::Position>(ship, 1280/2, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(ship, 50, 50);
	ecs::Ecs::addComponent<ecs::component::Drawable>(ship, 0, true);
	ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(ship);
	ecs::Ecs::addComponent<ecs::component::Sprite>(ship, "Sprite/Ship/BlueShip/BlueShip3.png");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(ship, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").x, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").y, true);

	ID enemy = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Keyboard>(ship);
	ecs::Ecs::addComponent<ecs::component::Position>(enemy, 1000, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(enemy, 0, 0);
	ecs::Ecs::addComponent<ecs::component::Drawable>(enemy, 0, true);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(enemy, ecs::graphical::Graphic::getTextureSize("Sprite/Enemy1/Enemy11.png").x, ecs::graphical::Graphic::getTextureSize("Sprite/Enemy1/Enemy11.png").y);
	ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(enemy, "Sprite/Enemy1");

	auto &keymap = ecs::Ecs::getComponentMap<ecs::component::Keyboard>()[ship].keyMap;
	keymap[KeyKeyboard::ESCAPE] = std::pair<bool, std::function<void(ID)>>(false, [&rtype](ID parent) {rtype._window->close();});
	keymap[KeyKeyboard::SPACE] = std::pair<bool, std::function<void(ID)>>(false, [](ID parent) {
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire).count() > ecs::Ecs::getComponentMap<game::Firerate>()[parent]._firerate)
		{
			TimedEventAdmin m;
			ID bullet = ecs::entity::Entity::getId();
			ecs::Ecs::addComponent<ecs::component::Speed>(bullet, 10, 0);
			ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 0, true);
			ecs::Ecs::addComponent<ecs::component::Position>(bullet, ecs::Ecs::getComponentMap<ecs::component::Position>()[parent].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[parent].y);
			ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, ecs::graphical::Graphic::getTextureSize("Sprite/ClassicBullet/ClassicBullet3.png").x, ecs::graphical::Graphic::getTextureSize("Sprite//ClassicBullet/ClassicBullet3.png").y, false, [parent](ID self, ID other){
					if (other != parent)
					{
						TimedEventAdmin t;
						ID explosion = ecs::entity::Entity::getId();
						ecs::Ecs::addComponent<ecs::component::Speed>(explosion, 0, 0);
						ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 0, true);
						ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
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

	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		rtype.update();
		game::Parallaxs::UpdateParallaxs();

		ecs::system::Controls::UpdateDeplacement();
		ecs::system::Speeds::UpdateSpeeds();

		auto x = static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0);
		std::this_thread::sleep_for(std::chrono::nanoseconds(x));
	}

}