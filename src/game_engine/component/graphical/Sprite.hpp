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
			shared = false;
		}

		Sprite(Sprite &&other):
			sprite(other.sprite),
			texture(other.texture),
			size(other.size),
			layer(other.layer),
			visible(other.visible),
			shared(other.shared)
		{
			other.sprite = nullptr;
			other.texture = nullptr;
		}
		Sprite(sf::Sprite *sprite, std::string path) {
			this->sprite = sprite;
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->layer = 1;
			this->visible = true;
			this->shared = true;
		}
		Sprite(std::string path) {
			this->texture = new sf::Texture();

			if (!this->texture->loadFromFile(path)) {
				exit(84);
			}
			this->sprite = new sf::Sprite(*this->texture);
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->layer = 1;
			this->visible = true;
			this->shared = false;
		}
		~Sprite() {
			if (!shared && sprite != nullptr && texture != nullptr) {
				delete sprite;
				delete texture;
				this->visible = false;
			}
		}

		Sprite& operator=( Sprite &&other) noexcept {
			this->sprite = other.sprite;
			this->texture = other.texture;
			this->size = other.size;
			this->layer = other.layer;
			this->visible = other.visible;
			this->shared = other.shared;
			other.sprite = nullptr;
			other.texture = nullptr;
			return *this;
		}

		sf::Sprite				*sprite;
		sf::Texture				*texture;
		ecs::core::Vector2<unsigned int>	size;
		unsigned int				layer;
		bool					visible;
		bool 					shared;
	};
}}