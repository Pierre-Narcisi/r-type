/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <string>
#include <iostream>
#include <sfml/Graphic.hpp>

namespace ecs {namespace component {
	struct Sprite {
		Sprite(std::string path) {
			id = graphical::Graphic::get().createSprite(path);
		}
		unsigned long id;
	};
}}