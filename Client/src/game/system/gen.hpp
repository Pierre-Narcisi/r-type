//
// Created by pierre on 20/11/2018.
//

#pragma once

#include <ecs/Ecs.hpp>
#include "component/ai.hpp"

namespace game {namespace system {
	class gen {
		public:
			gen();
			void updateGen();
		private:
			int _nb;
			unsigned int _time;
	};
}}