//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "../enemy.hpp"
#include <component/physic/Position.hpp>
#include <component/graphical/AnimatedSprite.hpp>
#include <component/physic/Speed.hpp>
#include <component/physic/Acceleration.hpp>
#include <component/physic/Hitbox.hpp>
#include <component/graphical/Drawable.hpp>
#include "core/Time.hpp"
#include "lib/TimedEvent/TimedEventAdmin.hpp"
#include <ecs/Ecs.hpp>
#include <ecs/DataBank.hpp>
#include "system/walls.hpp"

namespace game {
	class enemy2: public game::enemy {
		public:
			enemy2() = default;
			~enemy2() = default;
			void init(ID _id, int posx, int posy);
			void update(ID _id);
			int _time;
	};
}