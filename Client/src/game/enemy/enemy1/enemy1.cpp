//
// Created by pierre on 20/11/2018.
//

#include "enemy1.hpp"
#include "math.h"

namespace game {
	void enemy1::init(ID _id, int posx, int posy) {
		_time = ecs::core::Time::get(TimeUnit::Seconds);
		ecs::Ecs::addComponent<ecs::component::Drawable>(_id, 1, true);	
		ecs::Ecs::addComponent<game::component::Type>(_id, game::component::Type::Types::ENEMY);
		ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(_id, "assets/Sprite/Enemy1/", 4, ecs::core::Vector2<float>(40, 40));
		ecs::Ecs::addComponent<ecs::component::Position>(_id, posx, posy);
		ecs::Ecs::addComponent<ecs::component::Speed>(_id, -3.f, 0.f);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(_id, _id, false, static_cast<std::function<void(ID, ID)>>([](ID self, ID other){
			game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
			if (type._type == game::component::Type::Types::SHIP) {
				TimedEventAdmin t;
				ID explosion = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
				ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
				ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/BigExplosion", 10, ecs::core::Vector2<float>(70,70));
               			ecs::Ecs::deleteId(other);
               			ecs::Ecs::deleteId(self);
				t.addEvent(1000, Time::MilliSeconds, [explosion](){ecs::Ecs::deleteId(explosion);});
			}
		}));
	}

	void enemy1::update(ID _id) {
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto &speed = ecs::Ecs::getComponentMap<ecs::component::Speed>();

		speed[_id].y = sin(pos[_id].x / 70);
		if (pos[_id].x < 0) {
			ecs::Ecs::deleteId(_id);
		}
	}
}
