/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <unordered_map>
#include "AnimatedSprite.hpp"

namespace ecs {namespace component {
	struct AnimatedSpriteMap {
		AnimatedSpriteMap() {}
		AnimatedSpriteMap(std::string path) {
			std::set<std::string> sorted;
			if (boost::filesystem::exists(path)) {
				boost::filesystem::directory_iterator	endItr;
				for (boost::filesystem::directory_iterator itr(path)
				;itr != endItr
				;++itr) {
					if (boost::filesystem::is_directory(itr->status())) {
						sorted.insert(itr->path().filename().string());
					}
				}
				if (sorted.size() == 0) {
					std::cout << "src/game_engine/component/graphical/AnimatedSpriteMap: No folders found in \"" << path << "\"" << std::endl;
					exit(84);
				}
				for (auto it = sorted.begin(); it != sorted.end(); it++) {
					animatedSprites[*it] = AnimatedSprite(path + "/" + *it);
				}
			} else {
				std::cout << "src/game_engine/component/graphical/AnimatedSpriteMap: Missing directory \"" << path << "\"" << std::endl;
				exit(84);
			}

			if (animatedSprites.empty()) {
				std::cout << "src/game_engine/component/graphical/AnimatedSpriteMap: Directory must at least have 1 sprite" << std::endl;
				exit(84);
			}
			pos = *sorted.begin();
		}
		std::unordered_map<std::string, AnimatedSprite>	animatedSprites;
		std::string					pos;
	};
}}