//
// Created by pierre on 20/11/2018.
//

#include "enemy2.hpp"
#include "math.h"

namespace game {
	void enemy2::init(ID _id, int posx, int posy) {
		_time = ecs::core::Time::get(TimeUnit::Seconds);
		ecs::Ecs::addComponent<ecs::component::Drawable>(_id, 1, true);	
		ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(_id, "assets/Sprite/Enemy2/Enemy2walk/", 4, ecs::core::Vector2<float>(40, 40));
		ecs::Ecs::addComponent<ecs::component::Position>(_id, posx, posy);
		ecs::Ecs::addComponent<ecs::component::Speed>(_id, -0.5f, 0.f);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(_id, _id, true, static_cast<std::function<void(ID, ID)>>([](ID self, ID other){
			if (ecs::Ecs::idHasComponents<ecs::component::Keyboard>(other)) {
				ecs::Ecs::deleteId(other);
				ecs::Ecs::deleteId(self);
			}
		}));
	}

	void enemy2::update(ID _id) {
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto ship = ecs::Ecs::filter<ecs::component::Keyboard>();
		float dist;
		float res_dist = -1;
		ID res;

		if (pos[_id].x < -1) {
			ecs::Ecs::deleteId(_id);
		}

		if (ecs::core::Time::get(TimeUnit::Seconds) > _time + 1 && ship.size() > 0) {
			_time = ecs::core::Time::get(TimeUnit::Seconds);
			for (auto id :ship) {
				dist = sqrtf((pos[_id].x - pos[id].x) * (pos[_id].x - pos[id].x) + (pos[_id].y - pos[id].y) * (pos[_id].y - pos[id].y));
				if (dist > res_dist) {
					res_dist = dist;
					res = id;
				}
			}
			TimedEventAdmin m;
			ID bullet = ecs::entity::Entity::getId();
			float v1 = (pos[_id].x - pos[res].x);
			float v2 = (pos[_id].y - pos[res].y);
			double angle = std::atan2(-v1, -v2);
			ecs::Ecs::addComponent<ecs::component::Speed>(bullet, sinf(angle) * 7, cosf(angle) * 7);
			ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 1, true);
			ecs::Ecs::addComponent<ecs::component::Position>(bullet, ecs::Ecs::getComponentMap<ecs::component::Position>()[_id].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[_id].y);
			ecs::Ecs::addComponent<ecs::component::Sprite>(bullet, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["assets/Sprite/ClassicBullet/ClassicBullet2.png"], "assets/Sprite/ClassicBullet/ClassicBullet3.png");
			ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, bullet, false, [_id](ID self, ID other){
				if (other != _id) {
					TimedEventAdmin t;
					ID explosion = ecs::entity::Entity::getId();
					ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
					ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
					ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/BigExplosion", 10, ecs::core::Vector2<float>(70,70));
					if (!ecs::Ecs::idHasComponents<game::component::wall>(other)) {
               					ecs::Ecs::deleteId(other);
					}
               				ecs::Ecs::deleteId(self);
					t.addEvent(1000, Time::MilliSeconds, [explosion](){ecs::Ecs::deleteId(explosion);});
				}
        		});
			m.addEvent(5, Time::Seconds, [bullet](){ecs::Ecs::deleteId(bullet);});
		}
	}
}