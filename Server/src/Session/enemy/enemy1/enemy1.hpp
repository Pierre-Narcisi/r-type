//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "../enemy.hpp"
#include "ecs/Ecs.hpp"

namespace game {
	class enemy1: public game::enemy {
		public:
			enemy1() = default;
			~enemy1() = default;
			void init(ID _id, int posx, int posy, rtype::session::Session &session);
			void update(ID _id);
			long _time;
	};
}