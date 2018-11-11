/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <functional>
#include <core/CoreVector.hpp>
#include "ecs/Entity.hpp"

namespace ecs {namespace component {
	struct Hitbox {
		Hitbox() {}
		Hitbox(float width, float height) {
			this->width = width;
			this->height = height;
		}
		Hitbox(float width, float height, std::function<void(ID, ID)> function) {
			this->width = width;
			this->height = height;
			this->func = function;
		}
		float				height;
		float				width;
		std::function<void(ID, ID)>	func;
	};
}}