/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include <ecs/Ecs.hpp>
#include <component/physic/Position.hpp>
#include <component/physic/Hitbox.hpp>
#include "Hitboxs.hpp"

namespace ecs {namespace system {
	void Hitboxs::UpdateHitboxs() {
		auto ids = Ecs::filter<component::Position, component::Hitbox>();
		auto &poss = Ecs::getConponentMap<component::Position>();
		auto &hitboxs = Ecs::getConponentMap<component::Hitbox>();

		for (auto id : ids) {
			auto &pos1 = poss[id];
			auto &box1 = hitboxs[id];
			if (box1.func) {
				for (auto od: ids) {
					if (od != id) {
						auto &pos2 = poss[od];
						auto &box2 = hitboxs[od];

						if (box1.func && !((pos2.x >= pos1.x + box1.width / 2)
						      || (pos2.x + box2.width <= pos1.x)
						      || (pos2.y >= pos1.y + box1.height / 2)
						      || (pos2.y + box2.height / 2 <= pos1.y)))
							box1.func(id, od);
					}

				}
			}
		}
	}
}}