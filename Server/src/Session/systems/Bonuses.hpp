//
// Created by pierre on 20/11/2018.
//

#pragma once

#include <ecs/Ecs.hpp>
#include "Session/components/Bonuses.hpp"

namespace game {namespace system {
	class Bonuses {
	public:
		static void UpdateBonuses();
	};
}}