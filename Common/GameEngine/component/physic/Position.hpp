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
		float x = 0;
		float y = 0;
		Position &operator=(Position const &equal) {
			this->x = equal.x;
			this->y = equal.y;
			return *this;
		}
	};
}}