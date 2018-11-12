/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include "component/graphical/Sprite.hpp"
#include "component/physic/Position.hpp"
#include "ecs/Ecs.hpp"
#include "Sprites.hpp"

namespace ecs {namespace system {
	void Sprites::UpdateSprites() {
		auto ids = Ecs::filter<component::Position, component::Sprite>();
		auto &sprites = Ecs::getConponentMap<component::Sprite>();
		auto &positions = Ecs::getConponentMap<component::Position>();
		auto window = graphical::Graphic::getWindow();

		for (auto id = ids.begin(); id != ids.end(); id++) {
			if (!sprites[*id].visible) {
				ids.erase(id);
				id--;
			}
		}
		std::sort (ids.begin(), ids.end(), [](ID one, ID two){ return (
			Ecs::getConponentMap<component::Sprite>()[one].layer <
				Ecs::getConponentMap<component::Sprite>()[two].layer); });

		for (auto id : ids) {
			sprites[id].sprite->setPosition(positions[id].x, positions[id].y);
			window->draw(*sprites[id].sprite);
		}
	}
}}