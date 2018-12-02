//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "Session/Session.hpp"
#include "Session/enemy/enemy.hpp"

namespace game {
	class enemy2: public game::enemy {
		public:
			enemy2() = default;
			~enemy2() = default;
			void init(ID _id, int posx, int posy, rtype::session::Session &session);
			void update(ID _id, rtype::session::Session &session);
			int _time;
	};
}