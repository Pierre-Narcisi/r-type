/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <unordered_map>
#include "AnimatedSprite.hpp"

namespace ecs {namespace component {
	template <typename T>
	struct AnimatedSpriteMap {
		std::unordered_map<T, AnimatedSprite>	animatedSprites;
		T					pos;
	};
}}