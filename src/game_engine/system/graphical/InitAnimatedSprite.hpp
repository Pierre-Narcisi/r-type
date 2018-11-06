/*
** EPITECH PROJECT, 2021
** CPP_rtype_2018
** File description:
** Created by seb,
*/

#pragma once

#include <string>
#include "core/CoreVector.hpp"
#include "component/graphical/AnimatedSprite.hpp"

namespace ecs {namespace system {
		class InitAnimatedSprite {
		public:
			static void InitFromDir(ecs::component::AnimatedSprite &anim, std::string path, ecs::core::Vector2<int> pos,  ecs::core::Vector2<int> size, float framePerSecond);
		};
}}