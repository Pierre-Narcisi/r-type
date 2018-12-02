//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "ecs/Ecs.hpp"
#include "Session/components/ai.hpp"
#include "Session/Session.hpp"

namespace game {namespace system {
	class ai {
		public:
			static void updateAi(rtype::session::Session &session);
	};
}}