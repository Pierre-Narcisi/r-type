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
#include <system/graphical/Sprites.hpp>
#include <component/physic/Position.hpp>
#include <component/control/DeplacementKeyBoard.hpp>
#include <component/physic/Speed.hpp>
#include <system/physic/Speeds.hpp>
#include <component/physic/Hitbox.hpp>
#include <system/physic/Hitboxs.hpp>
#include "sfml/Graphic.hpp"
#include "core/Time.hpp"
#include "../lib/TimedEvent/TimedEventAdmin.hpp"

int main() {
	auto &rtype = ecs::graphical::Graphic::get();

	ID id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/Isaac.png");
	ecs::Ecs::addComponent<ecs::component::Position>(id, 0.f, 0.f);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(id);
	ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(id);
	ecs::Ecs::getConponentMap<ecs::component::Keyboard>()[id].keyMap[KeyKeyboard::SPACE]
	= std::pair<bool, std::function<void(ID)>>(false, [](ID parent){
		ID id = ecs::entity::Entity::getId();
		TimedEventAdmin m;

		ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/Bullet.png");
		ecs::Ecs::addComponent<ecs::component::Position>(id,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].x,
								 ecs::Ecs::getConponentMap<ecs::component::Position>()[parent].y);
		ecs::Ecs::addComponent<ecs::component::Speed>(id, 10.f, 10.f);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100, [](ID self, ID other){
			ecs::Ecs::deleteId(other);
			(void) self;
		});
		m.addEvent(2, Time::Seconds, [id](){ecs::Ecs::deleteId(id);});
	});

	id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/Isaac.png");
	ecs::Ecs::addComponent<ecs::component::Position>(id, 500.f, 500.f);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(id, 100, 100);


	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		rtype.update();
//		ecs::system::Update::game();
		rtype.update();

		ecs::system::Controls::UpdateDeplacement();
		ecs::system::Speeds::UpdateSpeeds();
		ecs::system::Hitboxs::UpdateHitboxs();


//		std::cout << "loop " << (ecs::core::Time::get(TimeUnit::MicroSeconds) - time)/16666 * 100 << "%\t" << ecs::core::Time::get(TimeUnit::MicroSeconds) - time << std::endl;

		usleep(static_cast<__useconds_t>(16666 - (time - ecs::core::Time::get(TimeUnit::MicroSeconds)) > 0 ? 16666 - (time - ecs::core::Time::get(TimeUnit::MicroSeconds)) : 0));
	}

}