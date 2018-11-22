/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <SFML/Audio/Sound.hpp>
#include <unordered_map>

namespace ecs {namespace component {
	struct Sound {
		Sound() {}
		std::unordered_map<std::string, sf::Sound> soundMap;
	};
}}