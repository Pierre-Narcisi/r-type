/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <list>
#include <boost/filesystem.hpp>
#include <iostream>
#include <set>
#include "ecs/Entity.hpp"
#include "core/CoreVector.hpp"
#include "core/Time.hpp"
#include "Sprite.hpp"

namespace ecs {namespace component {
	struct AnimatedSprite {
		AnimatedSprite() {
		}
		AnimatedSprite(std::string path) {
			std::set<std::string> sorted;
			if (boost::filesystem::exists(path)) {
				boost::filesystem::directory_iterator	endItr;
				for (boost::filesystem::directory_iterator itr(path); itr != endItr; ++itr) {
					if (boost::filesystem::is_regular(itr->status())) {
						sorted.insert(itr->path().string());
					}
				}
				for (auto it = sorted.begin(); it != sorted.end(); it++) {
					animation.emplace_back(*it);
				}
			} else {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Missing directory \"" << path << "\"" << std::endl;
				exit(84);
			}

			if (animation.size() == 0) {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Directory must at least have 1 sprite" << std::endl;
				exit(84);
			}
			interFrame = 1000000 / animation.size();
			oldTime = core::Time::get(TimeUnit::MicroSeconds);
			frame = 0;
			boxSize = graphical::Graphic::getTextureSize(*sorted.begin());
		}
		AnimatedSprite(std::string path, core::Vector2<float> size) {
			std::set<std::string> sorted;
			if (boost::filesystem::exists(path)) {
				boost::filesystem::directory_iterator	endItr;
				for (boost::filesystem::directory_iterator itr(path)
					;itr != endItr
					;++itr) {
					if (boost::filesystem::is_regular(itr->status())) {
						sorted.insert(itr->path().string());
					}
				}
				for (auto it = sorted.begin(); it != sorted.end(); it++) {
					animation.emplace_back(*it, size);
				}
			} else {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Missing directory \"" << path << "\"" << std::endl;
				exit(84);
			}

			if (animation.size() == 0) {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Directory must at least have 1 sprite" << std::endl;
				exit(84);
			}
			interFrame = 1000000 / animation.size();
			oldTime = core::Time::get(TimeUnit::MicroSeconds);
			frame = 0;
			boxSize = size;
		}
		AnimatedSprite(std::string path, int framesPerSecond) {
			std::set<std::string> sorted;
			if (boost::filesystem::exists(path)) {
				boost::filesystem::directory_iterator	endItr;
				for (boost::filesystem::directory_iterator itr(path)
					;itr != endItr
					;++itr) {
					if (boost::filesystem::is_regular(itr->status())) {
						sorted.insert(itr->path().string());
					}
				}
				for (auto it = sorted.begin(); it != sorted.end(); it++) {
					animation.emplace_back(*it);
				}
			} else {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Missing directory \"" << path << "\"" << std::endl;
				exit(84);
			}

			if (animation.size() == 0) {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Directory must at least have 1 sprite" << std::endl;
				exit(84);
			}
			interFrame = 1000000 / framesPerSecond;
			oldTime = core::Time::get(TimeUnit::MicroSeconds);
			frame = 0;
			boxSize = graphical::Graphic::getTextureSize(*sorted.begin());
		}
		AnimatedSprite(std::string path, int framesPerSecond, core::Vector2<float> size) {
			std::set<std::string> sorted;
			if (boost::filesystem::exists(path)) {
				boost::filesystem::directory_iterator	endItr;
				for (boost::filesystem::directory_iterator itr(path)
					;itr != endItr
					;++itr) {
					if (boost::filesystem::is_regular(itr->status())) {
						sorted.insert(itr->path().string());
					}
				}
				for (auto it = sorted.begin(); it != sorted.end(); it++) {
					animation.emplace_back(*it, size);
				}
			} else {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Missing directory \"" << path << "\"" << std::endl;
				exit(84);
			}

			if (animation.size() == 0) {
				std::cout << "src/game_engine/component/graphical/AnimatedSprite: Directory must at least have 1 sprite" << std::endl;
				exit(84);
			}
			interFrame = 1000000 / framesPerSecond;
			oldTime = core::Time::get(TimeUnit::MicroSeconds);
			frame = 0;
			boxSize = size;
		}

		std::vector<Sprite>		animation;
		long				interFrame;
		long 				oldTime;
		int				frame;
		core::Vector2<float>		boxSize;
	};
}}