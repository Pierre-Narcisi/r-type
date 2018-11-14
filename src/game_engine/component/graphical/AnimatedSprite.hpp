/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <list>
#include <dirent.h>
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
			DIR *dir;
			struct dirent *ent;
			std::set<std::string> sorted;
			if ((dir = opendir(path.c_str())) != NULL) {
				while ((ent = readdir(dir)) != NULL) {
					if (ent->d_type == DT_REG)
						sorted.insert(path + "/" + ent->d_name);
				}
				closedir(dir);
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
			layer = 0;
			interFrame = 1000000 / animation.size();
			oldTime = core::Time::get(TimeUnit::MicroSeconds);
			visible = true;
			frame = 0;
		}
		AnimatedSprite(std::string path, int framesPerSecond) {
			DIR *dir;
			struct dirent *ent;
			std::set<std::string> sorted;
			if ((dir = opendir(path.c_str())) != NULL) {
				while ((ent = readdir(dir)) != NULL) {
					if (ent->d_type == DT_REG)
						sorted.insert(path + "/" + ent->d_name);
				}
				closedir(dir);
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
			layer = 0;
			interFrame = 1000000 / framesPerSecond;
			oldTime = core::Time::get(TimeUnit::MicroSeconds);
			visible = true;
			frame = 0;
		}
		std::vector<Sprite>		animation;
		unsigned int			layer;
		long				interFrame;
		long 				oldTime;
		bool 				visible;
		int				frame;
	};
}}