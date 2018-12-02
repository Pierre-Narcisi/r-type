//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "Session/Session.hpp"
#include "ecs/Entity.hpp"

namespace game {namespace system {
	class Fire {
	public:
		static void shootFire(ID id, float spX, float spY, rtype::session::Session &session);
		static void shoot(ID id, rtype::session::Session &session);
	};
}}