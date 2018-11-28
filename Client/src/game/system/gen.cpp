//
// Created by pierre on 20/11/2018.
//

#include "core/Time.hpp"
#include "enemy/enemy1/enemy1.hpp"
#include "enemy/enemy2/enemy2.hpp"
#include "component/enemyFactory.hpp"
#include "gen.hpp"
#include <random>

namespace game {namespace system {
	gen::gen() {
		_nb = 0;
		_time = ecs::core::Time::get(TimeUnit::Seconds);
	}

	void gen::updateGen() {
		if (_time + _nb * 6 < ecs::core::Time::get(TimeUnit::Seconds)) {
			ID enemy = ecs::entity::Entity::getId();
			std::random_device generator;
			std::uniform_int_distribution<int> distribution(1,2);
			int my_rand = distribution(generator); 
			std::uniform_int_distribution<int> dist(3,10);
			int my_nb_rand = dist(generator);
			switch  (my_rand) {
				case 1:
					ecs::Ecs::addComponent<game::component::enemyFactory<enemy1>>(enemy, my_nb_rand);
					dist.reset();
					break;
				case 2:
					ecs::Ecs::addComponent<game::component::enemyFactory<enemy2>>(enemy, 1);
					dist.reset();
					break;
				default:
					break;
			}
			distribution.reset();
			_nb++;
		}
	}
}}