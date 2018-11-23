/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include "core/Time.hpp"
#include "core/CoreVector.hpp"

namespace ecs {namespace component {
	struct DeplacementMouse {
		DeplacementMouse() {
			this->speed = 100.f;
			this->lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
			this->lastPosition.x = 0;
			this->lastPosition.y = 0;
		}
		DeplacementMouse(float speed) {
			this->speed = speed;
			this->lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
			this->lastPosition.x = 0;
			this->lastPosition.y = 0;
		}
		DeplacementMouse(float speed, core::Vector2<int> position) {
			this->speed = speed;
			this->lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
			this->lastPosition = position;
		}
		float			speed;
		long 			lastMove;
		core::Vector2<int>	lastPosition;
	};
}}