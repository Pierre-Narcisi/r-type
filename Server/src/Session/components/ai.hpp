//
// Created by pierre on 20/11/2018.
//

#pragma once

#include <memory>
#include <iostream>
#include "Session/enemy/enemy.hpp"
#include "Session/Session.hpp"

namespace game {namespace component {
	struct ai {
		ai() {
		}
		ai(ID id, enemy *_enemy, int posx, int posy, rtype::session::Session &session) {
			_my_enemy_ai = std::shared_ptr<enemy>(_enemy);
			_my_enemy_ai->init(id, posx, posy, session);
		}

		std::shared_ptr<enemy>	_my_enemy_ai;
	};
}}