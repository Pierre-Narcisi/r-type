/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/
#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include "ecs/Ecs.hpp"
#include "Speeds.hpp"

namespace ecs {namespace system {
	void Speeds::UpdateSpeeds() {
		auto ids = ecs::Ecs::filter<component::Position, component::Speed>();
		auto &speed = ecs::Ecs::getConponentMap<component::Speed>();
		auto &position = ecs::Ecs::getConponentMap<component::Position>();

		for (auto id : ids) {
			position[id].x += speed[id].x;
			position[id].y += speed[id].y;
		}
	}
}}