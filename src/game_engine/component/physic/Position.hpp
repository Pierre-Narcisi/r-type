/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <core/CoreVector.hpp>

namespace ecs {namespace component {
	struct Position {
		Position() {
			x = 0.f;
			y = 0.f;
		}
		Position(float x, float y) {
			this->x = x;
			this->y = y;
		}
		float x;
		float y;
	};
}}