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
			shared = false;
		}

		Sprite(Sprite &&other):
			sprite(other.sprite),
			texture(other.texture),
			size(other.size),
			shared(other.shared)
		{
			other.sprite = nullptr;
			other.texture = nullptr;
		}
		Sprite(sf::Sprite *sprite, std::string path) {
			this->sprite = sprite;
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->shared = true;
		}
		Sprite(std::string path) {
			this->texture = new sf::Texture();

			if (!this->texture->loadFromFile(path)) {
				std::cout << "src/game_engine/component/graphical/Sprite: Couldn't load texture " << path << std::endl;
				exit(84);
			}
			this->sprite = new sf::Sprite(*this->texture);
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->shared = false;
		}
		Sprite(std::string path, bool visible) {
			this->texture = new sf::Texture();

			if (!this->texture->loadFromFile(path)) {
				std::cout << "src/game_engine/component/graphical/Sprite: Couldn't load texture " << path << std::endl;
				exit(84);
			}
			this->sprite = new sf::Sprite(*this->texture);
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->shared = false;
		}
		Sprite(std::string path, bool visible, unsigned int layer) {
			this->texture = new sf::Texture();

			if (!this->texture->loadFromFile(path)) {
				std::cout << "src/game_engine/component/graphical/Sprite: Couldn't load texture " << path << std::endl;
				exit(84);
			}
			this->sprite = new sf::Sprite(*this->texture);
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->shared = false;
		}
		~Sprite() {
			if (!shared) {
				delete sprite;
				delete texture;
			}
		}

		Sprite& operator=( Sprite &&other) noexcept {
			this->sprite = other.sprite;
			this->texture = other.texture;
			this->size = other.size;
			this->shared = other.shared;
			other.sprite = nullptr;
			other.texture = nullptr;
			return *this;
		}

		sf::Sprite				*sprite;
		sf::Texture				*texture;
		ecs::core::Vector2<unsigned int>	size;
		bool 					shared;
	};
}}