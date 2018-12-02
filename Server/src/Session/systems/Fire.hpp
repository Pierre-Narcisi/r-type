//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "ecs/Entity.hpp"

namespace game {namespace system {
	class Fire {
	public:
		static void shootFire(ID id, float spX, float spY);
		static void shoot(ID id);
	};
}}