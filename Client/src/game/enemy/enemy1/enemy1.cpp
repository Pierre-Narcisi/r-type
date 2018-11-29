//
// Created by pierre on 20/11/2018.
//

#include "enemy1.hpp"
#include "math.h"

namespace game {
	void enemy1::init(ID _id, int posx, int posy) {
		_time = ecs::core::Time::get(TimeUnit::Seconds);
		ecs::Ecs::addComponent<ecs::component::Drawable>(_id, 1, true);
		ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(_id, "assets/Sprite/Enemy1/", 4, ecs::core::Vector2<float>(50, 50));
		ecs::Ecs::addComponent<ecs::component::Hitbox>(_id, _id, true, static_cast<std::function<void(ID, ID)>>([](ID self, ID other){
			if (ecs::Ecs::idHasComponents<ecs::component::Keyboard>(other)) {

				ecs::Ecs::deleteId(other);
			ecs::Ecs::deleteId(self);
			}
		}));
		ecs::Ecs::addComponent<ecs::component::Position>(_id, posx, posy);
		ecs::Ecs::addComponent<ecs::component::Speed>(_id);
	}

	void enemy1::update(ID _id) {
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto &speed = ecs::Ecs::getComponentMap<ecs::component::Speed>();
		speed[_id].x = -3;
		speed[_id].y = sin(pos[_id].x / 70);
		if (pos[_id].x < -ecs::Ecs::getComponentMap<ecs::component::AnimatedSprite>()[_id].boxSize.x/2) {
			ecs::Ecs::deleteId(_id);
		}
	}
}
