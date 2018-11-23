//
// Created by pierre on 20/11/2018.
//

#include <ecs/DataBank.hpp>
#include <iostream>
#include "enemy/enemy.hpp"

namespace game {namespace component {
	struct ai {
		ai() {
		}
		ai(ID id, enemy *enemy) {
			_my_enemy_ai = enemy;
			_my_enemy_ai->init(id);
		}

		enemy	*_my_enemy_ai;
	};
}}