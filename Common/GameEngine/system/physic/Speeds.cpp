/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/
#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include "component/Types.hpp"
#define NOSPRITE
#include <component/physic/Hitbox.hpp>
#undef NOSPRITE
#include "ecs/Ecs.hpp"
#include "Speeds.hpp"

namespace ecs {namespace system {
	void Speeds::UpdateSpeeds() {
		auto ids = ecs::Ecs::filter<component::Position, component::Speed>();
		auto hitboxIds = ecs::Ecs::filter<component::Hitbox, component::Position>();
		auto &speed = ecs::Ecs::getComponentMap<component::Speed>();
		auto &position = ecs::Ecs::getComponentMap<component::Position>();

		auto &hitboxs = Ecs::getComponentMap<component::Hitbox>();
		component::Position tmpPos;
		bool comeY = false;
		bool comeX = false;

		for (auto id : ids) {
		if (ecs::Ecs::idHasComponents<component::Hitbox>(id)) {
				tmpPos = position[id];
				position[id].x += speed[id].x;
				position[id].y += speed[id].y;
				auto &pos1 = position[id];
				auto &box1 = hitboxs[id];
				for (auto od: hitboxIds) {
					if (od != id) {
						auto &pos2 = position[od];
						auto &box2 = hitboxs[od];

						if (!((pos2.x - box2.width >= pos1.x + box1.width) ||
							(pos2.x + box2.width <= pos1.x - box1.width) ||
							(pos2.y - box2.height >= pos1.y + box1.height) ||
							(pos2.y + box2.height <= pos1.y - box1.height))) {
							if (box1.func)
								box1.func(id, od);
							if (box2.collidable) {
								if ((pos2.x - box2.width >= tmpPos.x + box1.width) ||
								    (pos2.x + box2.width <= tmpPos.x - box1.width)) {
									if (box1.forceDeplacement)
										pos2.x += speed[id].x;
									if (box2.forceDeplacement)
										pos1.x += speed[od].x;
									comeX = true;
								}
								if ((pos2.y - box2.height >= tmpPos.y + box1.height) ||
								    (pos2.y + box2.height <= tmpPos.y - box1.height)) {
									if (box1.forceDeplacement)
										pos2.y += speed[id].y;
									if (box2.forceDeplacement)
										pos1.y += speed[od].y;
									comeY = true;
								}
							}
						}
					}
				}
				if (box1.forceDeplacement) {
					position[id].x += speed[id].x;
					position[id].y += speed[id].y;
				}
				if (box1.collidable) {
					if (comeX)
						position[id].x = tmpPos.x;
					if (comeY)
						position[id].y = tmpPos.y;
					comeX = comeY = false;
				}
			} else {
				position[id].x += speed[id].x;
				position[id].y += speed[id].y;
			}
		}
	}
}}