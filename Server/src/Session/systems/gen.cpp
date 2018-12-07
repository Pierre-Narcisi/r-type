//
// Created by pierre on 20/11/2018.
//

#include <random>
#include "GameEngine/core/Time.hpp"
#include "Session/enemy/enemy1/enemy1.hpp"
#include "Session/enemy/enemy2/enemy2.hpp"
#include "Session/enemy/enemy3/enemy3.hpp"
#include "Session/components/enemyFactory.hpp"
#include "gen.hpp"

namespace game {namespace system {
	gen::gen() {
		_nb = 0;
		_time = ecs::core::Time::get(TimeUnit::MilliSeconds);
	}

	void gen::updateGen(int playernb, rtype::session::Session &session) {
		if (!playernb) {
			if (_time + _nb * 1500 < ecs::core::Time::get(TimeUnit::MilliSeconds)) {
				_nb++;
			}
			return;
		}
		if (_time + _nb * (1500 / playernb) < ecs::core::Time::get(TimeUnit::MilliSeconds)) {
			TimedEventAdmin m;
			ID enemy = ecs::entity::Entity::getId();
			m.addEvent(10, Time::Seconds, [enemy, &session](){
				proto::Delete	pack{proto::Type::DELETE, session.getId(), 0, enemy};
				
				ecs::Ecs::deleteLater(enemy);
				session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
			});
			std::random_device generator;
			std::uniform_int_distribution<int> distribution(1, 3);
			int my_rand = distribution(generator); 
			std::uniform_int_distribution<int> dist(3,10);
			int my_nb_rand = dist(generator);
			switch  (my_rand) {
				case 1:
					ecs::Ecs::addComponent<game::component::enemyFactory<enemy1>>(enemy, my_nb_rand, 1, std::ref(session));
					dist.reset();
					break;
				case 2:
					ecs::Ecs::addComponent<game::component::enemyFactory<enemy2>>(enemy, 1, std::ref(session));
					dist.reset();
					break;
				case 3:
					ecs::Ecs::addComponent<game::component::enemyFactory<enemy3>>(enemy, my_nb_rand / 2, 3, std::ref(session));
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