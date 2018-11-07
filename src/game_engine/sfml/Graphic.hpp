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
#include "core/CoreVector.hpp"
#include "system/control/Controls.hpp"

namespace ecs {namespace graphical {
		class Graphic {
		private:
			struct Sprite {
				Sprite() {
					size = ecs::core::Vector2<unsigned int>(0, 0);
					pos = ecs::core::Vector2<float>(0, 0);
					visible = true;
				};
				sf::Sprite *sprite;
				sf::Texture *texture;
				ecs::core::Vector2<unsigned int> size;
				ecs::core::Vector2<float> pos;
				bool			visible;
			};

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
			}

			static Graphic &get();
			void update();
			bool isOpen();

			unsigned long createSprite(std::string path);

			/// Tools
			core::Vector2<unsigned int> getTextureSize(std::string path);

		private:
			sf::RenderWindow	*_window;
			sf::Event		_event;
			std::vector<unsigned int> _controllers;

			unsigned long _lastId;
			std::unordered_map<unsigned long, Sprite>	_spriteMap;
			std::unordered_map<unsigned long, Text>		_TextMap;
			std::unordered_map<unsigned long, Music>	_musicMap;
			std::unordered_map<unsigned long, Sound>	_soundMap;

			std::unordered_map<unsigned int, std::vector<unsigned long>> _layers;
			std::vector<unsigned long> _collidables;
		};
}}



