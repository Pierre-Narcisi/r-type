/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include <component/physic/Speed.hpp>
#include <component/physic/Acceleration.hpp>
#include <ecs/Ecs.hpp>
#include "Acceleration.hpp"

namespace ecs {namespace system {
	void Acceleration::UpdateAccelerations() {
		auto ids = ecs::Ecs::filter<component::Acceleration, component::Speed>();
		auto &acceleratiojn = ecs::Ecs::getConponentMap<component::Acceleration>();
		auto &speed = ecs::Ecs::getConponentMap<component::Speed>();

		for (auto id : ids) {
			speed[id].x += acceleratiojn[id].x;
			speed[id].y += acceleratiojn[id].y;
		}
	}
}}