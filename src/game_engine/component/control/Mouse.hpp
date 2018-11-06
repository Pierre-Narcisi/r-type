/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <unordered_map>
#include <core/CoreVector.hpp>

enum class KeyMouse {
	LCLICK,
	RCLICK,
	MCLICK
};

namespace ecs {namespace component {
	struct Mouse {
		std::unordered_map<KeyMouse, bool>	mouseMap;
		core::Vector2<int>			position;
	};
}}