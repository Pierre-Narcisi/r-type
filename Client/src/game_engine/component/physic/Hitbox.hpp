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
			this->width = width / 2;
			this->height = height / 2;
			this->collidable = false;
		}
		Hitbox(float width, float height, bool collidable) {
			this->width = width / 2;
			this->height = height / 2;
			this->collidable = collidable;
		}
		Hitbox(float width, float height, bool collidable, std::function<void(ID, ID)> function) {
			this->width = width / 2;
			this->height = height / 2;
			this->func = function;
			this->collidable = collidable;
		}
		float				height;
		float				width;
		std::function<void(ID, ID)>	func;
		bool 				collidable;
	};
}}