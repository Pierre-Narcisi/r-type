//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "../../lib/TimedEvent/TimedEventAdmin.hpp"
#include "component/ai.hpp"
#include "core/Time.hpp"
#include <random>

namespace game {namespace component {
	template <typename T>
	struct enemyFactory {
		enemyFactory() {
		}
		void createEnemy() {
			ID enemy = ecs::entity::Entity::getId();
			ecs::Ecs::addComponent<game::component::ai>(enemy, enemy, new T, 1300, y);
		}
		enemyFactory(int nb) {
			TimedEventAdmin admin;

			std::random_device generator;
			std::uniform_int_distribution<int> distribution(180,600);
			y = distribution(generator);
			for (int i = 0; i < nb; i++) {
				TimedEvent::get().addEvent(2 * i, Time::Seconds, std::bind(&enemyFactory::createEnemy, this));
			}
			distribution.reset();
		}
		enemyFactory(int nb, float freq) {
			TimedEventAdmin admin;

			std::random_device generator;
			std::uniform_int_distribution<int> distribution(180,600);
			y = distribution(generator);
			for (int i = 0; i < nb; i++) {
				TimedEvent::get().addEvent(freq * i, Time::Seconds, std::bind(&enemyFactory::createEnemy, this));
			}
			distribution.reset();
		}
		int y = 400;
	};
}}