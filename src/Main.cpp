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
#include "game/system/Parallaxs.hpp"

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
	ecs::Ecs::addComponent<ecs::component::Position>(ship, 1280/2, 720/2);
	ecs::Ecs::addComponent<ecs::component::Speed>(ship, 10, 10);
	ecs::Ecs::addComponent<ecs::component::Drawable>(ship, 0, true);
	ecs::Ecs::addComponent<ecs::component::DeplacementKeyBoard>(ship);
	ecs::Ecs::addComponent<ecs::component::AnimatedSpriteMap>(ship, "Sprite/Ship/BlueShip");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(ship, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").x, ecs::graphical::Graphic::getTextureSize("Sprite/Ship/BlueShip/up/BlueShip1.png").y);
	ecs::Ecs::addComponent<ecs::component::Keyboard>(ship);

	ID enemy = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Position>(enemy, 1000, 720/2);
	ecs::Ecs::addComponent<ecs::component::Drawable>(enemy, 0, true);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(ship, ecs::graphical::Graphic::getTextureSize("Sprite/Enemy1/Enemy11.png").x, ecs::graphical::Graphic::getTextureSize("Sprite/Enemy1/Enemy11.png").y);
	ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(enemy, "Sprite/Enemy1");



	auto &keymap = ecs::Ecs::getConponentMap<ecs::component::Keyboard>()[ship].keyMap;
	keymap[KeyKeyboard::KEY_Z] = std::pair<bool, std::function<void(ID)>>(false, [](ID self){
		ecs::Ecs::getConponentMap<ecs::component::AnimatedSpriteMap>()[self].pos = "up";
	});
	keymap[KeyKeyboard::KEY_S] = std::pair<bool, std::function<void(ID)>>(false, [](ID self){
		ecs::Ecs::getConponentMap<ecs::component::AnimatedSpriteMap>()[self].pos = "down";
	});
	keymap[KeyKeyboard::SPACE] = std::pair<bool, std::function<void(ID)>>(false, [](ID self){
		ID bullet = ecs::entity::Entity::getId();
		ecs::Ecs::addComponent<ecs::component::Speed>(bullet, 10, 0);
		ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 0, true);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, ecs::graphical::Graphic::getTextureSize("Sprite/ClassicBullet/ClassicBullet3.png").x, ecs::graphical::Graphic::getTextureSize("Sprite//ClassicBullet/ClassicBullet3.png").y);
		ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(bullet, "Sprite/ClassicBullet");
	});

	while (rtype.isOpen()) {
		long time = ecs::core::Time::get(TimeUnit::MicroSeconds);
		rtype.update();
		game::Parallaxs::UpdateParallaxs();

		ecs::system::Controls::UpdateDeplacement();
		ecs::system::Speeds::UpdateSpeeds();

		usleep(static_cast<unsigned int>(16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) > 0 ? 16666 - (ecs::core::Time::get(TimeUnit::MicroSeconds) - time) : 0));
	}

}