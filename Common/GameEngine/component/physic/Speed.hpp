/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

namespace ecs {namespace component {
		struct Speed {
			Speed() {
				x = 0.f;
				y = 0.f;
			}
			Speed(float x, float y) {
				this->x = x;
				this->y = y;
			}
			float x = 0;
			float y = 0;
		};
	}}