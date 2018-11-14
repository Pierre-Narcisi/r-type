/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include "ecs/Entity.hpp"
#include "component/graphical/AnimatedSprite.hpp"

namespace ecs {namespace system {
	class Graphicals {
	public:
		static void UpdateGraphicals();
		static void UpdateAnimatedSprite(component::AnimatedSprite &animated);
	};
}}



