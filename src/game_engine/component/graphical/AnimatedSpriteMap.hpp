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
			DIR *dir;
			struct dirent *ent;
			std::set<std::string> sorted;
			if ((dir = opendir(path.c_str())) != NULL) {
				while ((ent = readdir(dir)) != NULL) {
					if (ent->d_type == DT_DIR && ent->d_name != std::string(".") && ent->d_name != std::string("..")) {
						sorted.insert(ent->d_name);
					}
				}
				closedir(dir);
				if (sorted.size() == 0) {
					std::cout << "src/game_engine/component/graphical/AnimatedSpriteMap: No folders found in \"" << path << "\"" << std::endl;
					exit(84);
				}
				for (auto name : sorted) {
					animatedSprites[name] = AnimatedSprite(path + "/" + name);
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