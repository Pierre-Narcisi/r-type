/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include <iostream>
#include <zconf.h>
#include <ecs/Entity.hpp>
#include <ecs/Ecs.hpp>
#include <component/graphical/Sprite.hpp>
#include <system/graphical/Graphicals.hpp>
#include <component/physic/Position.hpp>
#include <component/control/DeplacementKeyBoard.hpp>
#include <component/physic/Speed.hpp>
#include <system/physic/Speeds.hpp>
#include <component/physic/Hitbox.hpp>
#include <component/graphical/AnimatedSprite.hpp>
#include <component/graphical/Drawable.hpp>
#include <ecs/DataBank.hpp>
#include <component/audio/Sound.hpp>
#include <component/control/DeplacementMouse.hpp>
#include "sfml/Graphic.hpp"
#include "core/Time.hpp"
#include "../lib/TimedEvent/TimedEventAdmin.hpp"

int main() {
	auto &rtype = ecs::graphical::Graphic::get();
	ecs::DataBank<std::string, sf::SoundBuffer>::get().creator = [](std::string path){
		sf::SoundBuffer buffer;
		buffer.loadFromFile(path);
		return buffer;
	};

	ID banane = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Drawable>(banane, 1, true);
	ecs::Ecs::addComponent<ecs::component::Position>(banane, 0.f, 0.f);
	ecs::Ecs::addComponent<ecs::component::Speed>(banane, 0, 12);
	ecs::Ecs::addComponent<ecs::component::Sprite>(banane, "./assets/Isaac.png");

	ID loick = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Drawable>(loick, 1, true);
	ecs::Ecs::addComponent<ecs::component::Position>(loick, 0.f, 0.f);
	ecs::Ecs::addComponent<ecs::component::Speed>(loick, 12, 0);
	ecs::Ecs::addComponent<ecs::component::Sprite>(loick, "./assets/Bullet.png", true, 2);


	ID id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
	ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/Isaac.png");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, true);
	ecs::Ecs::addComponent<ecs::component::Position>(id, 0.f, 0.f);
	ecs::Ecs::addComponent<ecs::component::Speed>(id, 0.f, 0.f);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(id);
	ecs::Ecs::addComponent<ecs::component::Mouse>(id);
	ecs::Ecs::addComponent<ecs::component::DeplacementMouse>(id, 300.f);
	ecs::Ecs::getConponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::ESCAPE]
	= std::pair<bool, std::function<void(ID)>>(false, [](ID parent){
		(void) parent;
		ecs::graphical::Graphic::get()._window->close();
	});
	ecs::Ecs::getConponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::LEFT_ARROW]
	= std::pair<bool, std::function<void(ID)>>(false, [](ID parent){
		ID id = ecs::entity::Entity::getId();
		TimedEventAdmin m;

		ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
		ecs::Ecs::addComponent<ecs::component::Sprite>(id, ecs::graphical::Graphic::loadedSprite("./assets/Bullet.png"), "./assets/Bullet.png");
		ecs::Ecs::addComponent<ecs::component::Position>(id,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].x,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].y);
		ecs::Ecs::addComponent<ecs::component::Speed>(id, -10.f, 0.f);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, false, [parent](ID self, ID other){
			if (other != parent && ecs::Ecs::getConponentMap<ecs::component::Sprite>()[other].shared == false)
				ecs::Ecs::deleteId(other);
			(void) self;
		});
		m.addEvent(2, Time::Seconds, [id](){ecs::Ecs::deleteId(id);});
	});
	ecs::Ecs::getConponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::UP_ARROW]
		= std::pair<bool, std::function<void(ID)>>(false, [](ID parent){
		ID id = ecs::entity::Entity::getId();
		TimedEventAdmin m;

		ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
		ecs::Ecs::addComponent<ecs::component::Sprite>(id, ecs::graphical::Graphic::loadedSprite("./assets/Bullet.png"), "./assets/Bullet.png");
		ecs::Ecs::addComponent<ecs::component::Position>(id,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].x,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].y);
		ecs::Ecs::addComponent<ecs::component::Speed>(id, 0.f, -10.f);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, false, [parent](ID self, ID other){
			if (other != parent && ecs::Ecs::getConponentMap<ecs::component::Sprite>()[other].shared == false)
				ecs::Ecs::deleteId(other);
			(void) self;
		});
		m.addEvent(2, Time::Seconds, [id](){ecs::Ecs::deleteId(id);});
	});
	ecs::Ecs::getConponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::RIGHT_ARROW]
		= std::pair<bool, std::function<void(ID)>>(false, [](ID parent){
		ID id = ecs::entity::Entity::getId();
		TimedEventAdmin m;

		ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
		ecs::Ecs::addComponent<ecs::component::Sprite>(id, ecs::graphical::Graphic::loadedSprite("./assets/Bullet.png"), "./assets/Bullet.png");
		ecs::Ecs::addComponent<ecs::component::Position>(id,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].x,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].y);
		ecs::Ecs::addComponent<ecs::component::Speed>(id, 10.f, 0.f);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, false, [parent](ID self, ID other){
			if (other != parent && ecs::Ecs::getConponentMap<ecs::component::Sprite>()[other].shared == false)
				ecs::Ecs::deleteId(other);
			ecs::Ecs::getConponentMap<ecs::component::Sound>()[parent].soundMap["attack"].play();
			(void) self;
		});
		m.addEvent(2, Time::Seconds, [id](){ecs::Ecs::deleteId(id);});
	});
	ecs::Ecs::getConponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::DOWN_ARROW]
		= std::pair<bool, std::function<void(ID)>>(false, [](ID parent){
		ID id = ecs::entity::Entity::getId();
		TimedEventAdmin m;

		ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
		ecs::Ecs::addComponent<ecs::component::Sprite>(id, ecs::graphical::Graphic::loadedSprite("./assets/Bullet.png"), "./assets/Bullet.png");
		ecs::Ecs::addComponent<ecs::component::Position>(id,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].x,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].y);
		ecs::Ecs::addComponent<ecs::component::Speed>(id, 0.f, 10.f);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, false, [parent](ID self, ID other){
			if (other != parent && ecs::Ecs::getConponentMap<ecs::component::Sprite>()[other].shared == false)
				ecs::Ecs::deleteId(other);
			(void) self;
		});
		m.addEvent(2, Time::Seconds, [id](){ecs::Ecs::deleteId(id);});
	});
	ecs::Ecs::addComponent<ecs::component::Sound>(id);
	ecs::Ecs::getConponentMap<ecs::component::Sound>()[id].soundMap["attack"].setBuffer(ecs::DataBank<std::string, sf::SoundBuffer>::get("./assets/sounds/death.wav"));

	id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
	ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/Isaac.png");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, true);
	ecs::Ecs::addComponent<ecs::component::Position>(id, 100.f, 100.f);
	ecs::Ecs::addComponent<ecs::component::Speed>(id, 0.f, 0.f);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(id);
	ecs::Ecs::addComponent<ecs::component::Mouse>(id);
	ecs::Ecs::addComponent<ecs::component::DeplacementMouse>(id, 300.f);

	id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
	ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/Isaac.png");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, true);
	ecs::Ecs::addComponent<ecs::component::Position>(id, 200.f, 200.f);
	ecs::Ecs::addComponent<ecs::component::Speed>(id, 0.f, 0.f);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(id);
	ecs::Ecs::addComponent<ecs::component::Mouse>(id);
	ecs::Ecs::addComponent<ecs::component::DeplacementMouse>(id, 300.f);

	id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
	ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/Isaac.png");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, true);
	ecs::Ecs::addComponent<ecs::component::Position>(id, 300.f, 300.f);
	ecs::Ecs::addComponent<ecs::component::Speed>(id, 0.f, 0.f);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(id);
	ecs::Ecs::addComponent<ecs::component::Mouse>(id);
	ecs::Ecs::addComponent<ecs::component::DeplacementMouse>(id, 300.f);

	id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Drawable>(id, 1, true);
	ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/Bullet.png");
	ecs::Ecs::addComponent<ecs::component::Position>(id, 500.f, 500.f);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, true);
	ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(id, "./assets", 4);

	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		rtype.update();

		ecs::system::Controls::UpdateDeplacement();
		ecs::system::Speeds::UpdateSpeeds();

		usleep(static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0));
	}

}