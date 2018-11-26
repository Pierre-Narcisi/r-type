//
// Created by pierre on 20/11/2018.
//

#include <ecs/Ecs.hpp>

#pragma once

namespace game {
	class enemy {
		public:
			enemy() = default;
			~enemy() = default;
			virtual void init(ID _id, int posx, int posy) = 0;
			virtual void update(ID _id) = 0;
	};
}