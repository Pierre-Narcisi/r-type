//
// Created by pierre on 20/11/2018.
//

#include "ai.hpp"

namespace game {namespace system {
	void ai::updateAi() {
		auto ids = ecs::Ecs::filter<component::ai>();
		auto &ai = ecs::Ecs::getComponentMap<component::ai>();

		for (auto id : ids) {
			ai[id]._my_enemy_ai->update(id);
		}
	}
}}