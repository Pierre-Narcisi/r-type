//
// Created by pierre on 27/11/2018.
//

#pragma once

#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include "component/physic/Hitbox.hpp"
#include <component/graphical/Sprite.hpp>
#include <component/graphical/Drawable.hpp>
#include <ecs/DataBank.hpp>
#include <ecs/Ecs.hpp>
#include "component/wall.hpp"


namespace game {namespace system {
	class walls {
		public:
			void updateUp();
			void updateDown();
			void updateWalls();
		private:
			ID _bindUp = -1;
			ID _bindDown = -1;
	};
}}