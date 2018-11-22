/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include <iostream>
#include <unistd.h>
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
#include "game/component/Parallax.hpp"
#include "game/system/Parallaxs.hpp"

int main() {
	auto &rtype = ecs::graphical::Graphic::get();
	ecs::DataBank<std::string, sf::SoundBuffer>::get().creator = [](std::string path){
		sf::SoundBuffer buffer;
		buffer.loadFromFile(path);
		return buffer;
	};

	ID id = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<game::Parallax>(id, "assets/space.png", 100.f);

	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		rtype.update();
		game::Parallaxs::UpdateParallaxs();

		ecs::system::Controls::UpdateDeplacement();
		ecs::system::Speeds::UpdateSpeeds();

		usleep(static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0));
	}

}