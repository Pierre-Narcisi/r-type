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
		Sprite() {
			layer = 0;
			visible = false;
		}
		Sprite(sf::Sprite *sprite, std::string path) {
			this->sprite = sprite;
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->layer = 1;
			this->visible = true;
		}
		Sprite(std::string path) {
			this->texture = new sf::Texture();

			if (!this->texture->loadFromFile(path)) {
				std::cout << "src/game_engine/component/grapicalSprite: Could not load texture " << path << std::endl;
				exit(84);
			}
			this->sprite = new sf::Sprite(*this->texture);
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->layer = 1;
			this->visible = true;
		}
		sf::Sprite				*sprite;
		sf::Texture				*texture;
		ecs::core::Vector2<unsigned int>	size;
		unsigned int				layer;
		bool					visible;
	};
}}