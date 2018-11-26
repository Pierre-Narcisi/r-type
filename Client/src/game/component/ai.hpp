//
// Created by pierre on 20/11/2018.
//

#pragma once

#include <iostream>
#include "enemy/enemy.hpp"

namespace game {namespace component {
	struct ai {
		ai() {
		}
		ai(ID id, enemy *enemy, int posx, int posy) {
			_my_enemy_ai = enemy;
			_my_enemy_ai->init(id, posx, posy);
		}

		enemy	*_my_enemy_ai;
	};
}}