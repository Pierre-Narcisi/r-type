//
// Created by pierre on 20/11/2018.
//

#include "Bonuses.hpp"

namespace game {namespace system {
	void Bonuses::UpdateBonuses() {
		auto ids = ecs::Ecs::filter<ecs::component::Position, game::component::Bonuses>();
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto &bon = ecs::Ecs::getComponentMap<game::component::Bonuses>();

		for (auto id : ids) {
			bon[id].x = pos[id].x;
			bon[id].y = pos[id].y;
		}
	}
}}