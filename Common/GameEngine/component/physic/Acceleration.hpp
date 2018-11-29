/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

namespace ecs {namespace component {
	struct Acceleration {
		Acceleration() {
			x = 0.f;
			y = 0.f;
		}
		Acceleration(float x, float y) {
			this->x = x;
			this->y = y;
		}
		float x;
		float y;
	};
}}