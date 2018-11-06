/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <list>
#include "core/CoreVector.hpp"

namespace ecs {namespace component {
	struct AnimatedSprite {
		std::list<unsigned long>	animation;
		long				interFrame;
		long 				oldTime;
		ecs::core::Vector2<int>		pos;
		int				frame;
	};
}}