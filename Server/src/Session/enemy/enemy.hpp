//
// Created by pierre on 20/11/2018.
//

#if !defined(_ENEMY_HPP)
#define _ENEMY_HPP

#include "Session/Session.hpp"
#include "ecs/Ecs.hpp"

namespace game {
	class enemy {
		public:
			enemy() = default;
			~enemy() = default;
			virtual void init(ID _id, int posx, int posy, rtype::session::Session &session) = 0;
			virtual void update(ID _id, rtype::session::Session &session) = 0;
	};
}

#endif // _ENEMY_HPP