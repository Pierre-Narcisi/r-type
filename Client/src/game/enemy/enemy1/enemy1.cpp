//
// Created by pierre on 20/11/2018.
//

#include "enemy1.hpp"
#include "math.h"

namespace game {
	void enemy1::init(ID _id, int posx, int posy) {
		_time = ecs::core::Time::get(TimeUnit::Seconds);
		ecs::Ecs::addComponent<ecs::component::Drawable>(_id, 1, true);	
		ecs::Ecs::addComponent<ecs::component::Hitbox>(_id, 100, 100, true);
		ecs::Ecs::addComponent<ecs::component::Position>(_id, posx, posy);
		ecs::Ecs::addComponent<ecs::component::Speed>(_id, -0.5f, -0.5f);
		ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(_id, "./Sprite/Enemy1/", 4);
	}

	void enemy1::update(ID _id) {
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto &speed = ecs::Ecs::getComponentMap<ecs::component::Speed>();
		speed[_id].x = -1;
		speed[_id].y = sin(pos[_id].x / 50);
		if (_time + 10 < ecs::core::Time::get(TimeUnit::Seconds)) {
			ecs::Ecs::deleteId(_id);
		}
	}
}