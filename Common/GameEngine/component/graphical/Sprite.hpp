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

		Sprite(Sprite &&other): sprite(other.sprite), texture(other.texture), size(other.size), shared(other.shared) {
			other.sprite = nullptr;
			other.texture = nullptr;
		}
		Sprite(graphical::BundleSprite &bundled, std::string path) {
			this->sprite = bundled.sprite;
			this->size = graphical::Graphic::getTextureSize(path);
			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);
			this->shared = true;
			this->boxSize = size;
		}
		Sprite(graphical::BundleSprite &bundled, std::string path, core::Vector2<float> size) {
			this->sprite = bundled.sprite;
			this->size = graphical::Graphic::getTextureSize(path);

			float y = size.y / this->size.y;
			float x = size.x / this->size.x;

			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);

			if (y < x) {
				this->sprite->setScale(y, y);
				this->size.x = this->size.x * y;
				this->size.y = this->size.y * y;
			} else {
				this->sprite->setScale(x, x);
				this->size.x = this->size.x * x;
				this->size.y = this->size.y * x;
			}

			this->shared = true;
			this->boxSize = size;
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
			this->boxSize = size;
		}

		Sprite(std::string path, core::Vector2<float> size) {
			this->texture = new sf::Texture();

			if (!this->texture->loadFromFile(path)) {
				std::cout << "src/game_engine/component/graphical/Sprite: Couldn't load texture " << path << std::endl;
				exit(84);
			}
			this->sprite = new sf::Sprite(*this->texture);
			this->size = graphical::Graphic::getTextureSize(path);

			float y = size.y / this->size.y;
			float x = size.x / this->size.x;

			this->sprite->setOrigin(this->size.x / 2, this->size.y / 2);

			if (y < x) {
				this->sprite->setScale(y, y);
				this->size.x = this->size.x * y;
				this->size.y = this->size.y * y;
			} else {
				this->sprite->setScale(x, x);
				this->size.x = this->size.x * x;
				this->size.y = this->size.y * x;
			}

			this->shared = false;
			this->boxSize = size;
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
		ecs::core::Vector2<float>		size;
		ecs::core::Vector2<float>		boxSize;
		bool 					shared;
	};
}}