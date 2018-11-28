/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <iostream>
#include "core/CoreVector.hpp"
#include "system/control/Controls.hpp"

namespace ecs {namespace graphical {

		struct BundleSprite {
				BundleSprite() {
					sprite = nullptr;
					texture = nullptr;
				}
				sf::Sprite *sprite;
				sf::Texture *texture;
		};

		class Graphic {
		private:
			struct Text {
				Text() {
					pos = ecs::core::Vector2<int>(0, 0);
					visible = true;
				};
				sf::Text *text;
				sf::Font *font;
				ecs::core::Vector2<int> pos;
				bool visible;
			};

			struct Music {
				Music() {
					music = new sf::Music();
				};
				sf::Music *music;
			};

			struct Sound {
				Sound() {
					sound = new sf::Sound();
				};
				sf::Sound *sound;
				sf::SoundBuffer buffer;
			};

		public:

			Graphic() : _lastId(0) {
				sf::VideoMode mode;
				mode.width = 1280;
				mode.height = 720;
				mode.bitsPerPixel = 32;
				_window = new sf::RenderWindow(mode, "Game", sf::Style::Resize | sf::Style::Close);
				_window->setFramerateLimit(120);
			}

			static Graphic &get();
			void update();
			bool isOpen();

			static sf::RenderWindow *getWindow() {
				return (get()._window);
			}

			static sf::Sprite *loadedSprite(std::string path) {
				auto &bundle = get()._chargedSprites[path];
				if (bundle.sprite != nullptr)
					return (bundle.sprite);
				std::cout << "loaded sprite once" << std::endl;
				bundle.texture = new sf::Texture();

				if (!bundle.texture->loadFromFile(path)) {
					std::cout << "src/game_engine/sfml/Graphic: Could not load texture " << path << std::endl;
					bundle.texture = nullptr;
				}
				bundle.sprite = new sf::Sprite(*bundle.texture);
				return (bundle.sprite);
			}

			/// Tools
			static core::Vector2<float> getTextureSize(std::string path) {
				sf::Texture tmp;

				if (!tmp.loadFromFile(path))
					return core::Vector2<float>();
				auto size = tmp.getSize();
				return core::Vector2<float>(size.x, size.y);
			}

			sf::RenderWindow				*_window;
			std::unordered_map<std::string, BundleSprite>	_chargedSprites;
		private:
			sf::Event					_event;
			std::vector<unsigned int>			_controllers;

			unsigned long					_lastId;
		};
}}



