/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#include <dirent.h>
#include <set>
#include <iostream>
#include "core/Time.hpp"
#include "InitAnimatedSprite.hpp"

namespace ecs{namespace system {
	void InitAnimatedSprite::InitFromDir(
		ecs::component::AnimatedSprite	&anim,
		std::string			path,
		ecs::core::Vector2<int>		pos,
		ecs::core::Vector2<int>		size,
		float framePerSecond) {
		anim.pos = pos;
		anim.interFrame = static_cast<long>(1000000.0 / framePerSecond);
		anim.frame = 0;
		anim.oldTime = ecs::core::Time::get(TimeUnit::NanoSeconds);
		DIR *dir;
		struct dirent *ent;
		std::set<std::string> sorted;
		if ((dir = opendir(path.c_str())) != NULL) {
			while ((ent = readdir(dir)) != NULL) {
				sorted.insert(path + "/" + ent->d_name);
			}
			closedir(dir);
			for (auto it = sorted.begin(); it != sorted.end(); it++) {
				if (*it != path + "/." && *it != path + "/..") {
					/*auto sprite = game::Game::get().getGraphicalLib()->createSprite(*it, pos, size, 1);
					game::Game::get().getGraphicalLib()->setVisible(sprite, false);
					anim.animation.push_back(sprite);*/
				}
			}
		} else {
			std::cout << "Missing directory \"" << path << "\"" << std::endl;
			exit(84);
		}

		if (anim.animation.size() == 0) {
			std::cout << "Directory must at least have 1 sprite" << std::endl;
			exit(84);
		}
	}
}}