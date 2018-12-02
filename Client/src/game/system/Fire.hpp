//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "component/Inventory.hpp"
#include <ecs/Entity.hpp>
#include <ecs/Ecs.hpp>
#include <component/graphical/Sprite.hpp>
#include <component/physic/Position.hpp>
#include <component/physic/Speed.hpp>
#include <component/physic/Hitbox.hpp>
#include "core/Time.hpp"
#include "lib/TimedEvent/TimedEventAdmin.hpp"
#include "Session/components/Types.hpp"
#include "Session/components/Firerate.hpp"
#include <ecs/DataBank.hpp>
#include <math.h>

namespace game {namespace system {
	class Fire {
	public:
		static void shootFire(ID id, float spX, float spY);
		static void shoot(ID id);
	};
}}