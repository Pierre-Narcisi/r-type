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
#include "sfml/Graphic.hpp"
#include "core/Time.hpp"

int main() {
	auto &rtype = ecs::graphical::Graphic::get();

	ID id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Sprite>(id, "./assets/r-typesheet1.gif");


	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		rtype.update();
//		ecs::system::Update::game();
		rtype.update();

//		std::cout << "loop " << (ecs::core::Time::get(TimeUnit::MicroSeconds) - time)/16666 * 100 << "%\t" << ecs::core::Time::get(TimeUnit::MicroSeconds) - time << std::endl;

		usleep(static_cast<__useconds_t>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0));
	}

}