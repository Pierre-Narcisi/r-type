//
// Created by pierre on 20/11/2018.
//

#pragma once

#include <ecs/Ecs.hpp>
#include "Session/Session.hpp"
#include "Session/components/ai.hpp"

namespace game {namespace system {
	class gen {
		public:
			gen();
			void updateGen(rtype::session::Session &session);
		private:
			int _nb;
			long _time;
	};
}}