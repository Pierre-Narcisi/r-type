/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

namespace ecs {namespace component {
	struct Drawable {
		Drawable() {
			this->layer = 0;
			this->visible = false;
		}
		Drawable(unsigned int layer, bool visible) {
			this->layer = layer;
			this->visible = visible;
		}
		unsigned int				layer;
		bool					visible;
	};
}}