//
// Created by pierre on 20/11/2018.
//

#include "enemy2.hpp"
#include "math.h"

namespace game {
	void enemy2::init(ID _id, int posx, int posy) {
		_time = ecs::core::Time::get(TimeUnit::Seconds);
		ecs::Ecs::addComponent<ecs::component::Drawable>(_id, 1, true);	
		ecs::Ecs::addComponent<ecs::component::Hitbox>(_id, 100, 100, true, [](ID self, ID other){
			if (ecs::Ecs::idHasComponents<ecs::component::Keyboard>(other)) {
				ecs::Ecs::deleteId(other);
				ecs::Ecs::deleteId(self);
			}
		});
		ecs::Ecs::addComponent<ecs::component::Position>(_id, posx, posy);
		ecs::Ecs::addComponent<ecs::component::Speed>(_id, -5.f, 3.f);
		ecs::Ecs::addComponent<ecs::component::Acceleration>(_id, 0, 1);
		ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(_id, "assets/Sprite/Enemy2/Enemy2walk/", 4);
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
				dist = sqrt(powf(2, (pos[_id].x - pos[id].x)) + powf(2, (pos[_id].y - pos[_id].y)));
				if (dist > res_dist) {
					res_dist = dist;
					res = id;
				}
			}
			res_dist / (pos[_id].x - pos[res].x);


			ID bullet = ecs::entity::Entity::getId();
			ecs::Ecs::addComponent<ecs::component::Speed>(bullet, 10, 0);
			ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 1, true);
			ecs::Ecs::addComponent<ecs::component::Position>(bullet, ecs::Ecs::getComponentMap<ecs::component::Position>()[parent].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[parent].y);
			ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, 5, 5, false, [parent](ID self, ID other){ if(other!=parent){ecs::Ecs::deleteId(other);}});
			/*ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, ecs::graphical::Graphic::getTextureSize("assets/Sprite/ClassicBullet/ClassicBullet3.png").x, ecs::graphical::Graphic::getTextureSize("assets/Sprite//ClassicBullet/ClassicBullet3.png").y, false, [parent](ID self, ID other){
				if (other != parent) {
					TimedEventAdmin t;
					ID explosion = ecs::entity::Entity::getId();
					ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
					ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
					ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/Explosion", 12);
               		ecs::Ecs::deleteId(other);
               		ecs::Ecs::deleteId(self);
					t.addEvent(500, Time::MilliSeconds, [explosion](){ecs::Ecs::deleteId(explosion);});
				}
        	});*/
			ecs::Ecs::addComponent<ecs::component::Sprite>(bullet, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["assets/Sprite/ClassicBullet/ClassicBullet3.png"], "assets/Sprite/ClassicBullet/ClassicBullet3.png");
			m.addEvent(10, Time::Seconds, [bullet](){ecs::Ecs::deleteId(bullet);});
			ecs::Ecs::getComponentMap<game::Firerate>()[parent]._lastfire = std::chrono::system_clock::now();

		}
	}
}