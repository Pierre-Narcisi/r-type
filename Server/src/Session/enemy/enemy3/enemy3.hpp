//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "ecs/Ecs.hpp"
#include "Session/enemy/enemy.hpp"

namespace game {
	class enemy3: public game::enemy {
		public:
			enemy3() = default;
			~enemy3() = default;
			void init(ID _id, int posx, int posy, rtype::session::Session &session);
			void update(ID _id, rtype::session::Session &session);
			int _time;
	};
}