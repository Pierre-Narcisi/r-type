//
// Created by pierre on 20/11/2018.
//

#include <math.h>
#include "component/Inventory.hpp"
#include "ecs/Ecs.hpp"
#include "component/physic/Position.hpp"
#include "component/physic/Speed.hpp"
#include "component/physic/Hitbox.hpp"
#include "core/Time.hpp"
#include "lib/TimedEvent/TimedEventAdmin.hpp"
#include "component/Types.hpp"
#include "component/Firerate.hpp"
#include "ecs/DataBank.hpp"
#include "Fire.hpp"

namespace game {namespace system {
	void Fire::shootFire(ID id, float spX, float spY) {
		
			TimedEventAdmin m;
			ID bullet = ecs::entity::Entity::getId();
			ecs::Ecs::addComponent<ecs::component::Speed>(bullet, spX, spY);
			//ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 1, true);
			ecs::Ecs::addComponent<game::component::Type>(bullet, game::component::Type::Types::BULLET_SHIP);
			
			ecs::Ecs::addComponent<ecs::component::Position>(bullet, ecs::Ecs::getComponentMap<ecs::component::Position>()[id].x + 100, ecs::Ecs::getComponentMap<ecs::component::Position>()[id].y);
			//ecs::Ecs::addComponent<ecs::component::Sprite>(bullet, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["assets/Sprite/ClassicBullet/ClassicBullet3.png"], "assets/Sprite/ClassicBullet/ClassicBullet3.png");
			ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, 5, 5, false, [id](ID self, ID other) {
				game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
				if (type._type == game::component::Type::Types::BULLET_ENEMY || type._type == game::component::Type::Types::ENEMY) {
					TimedEventAdmin t;
					ID explosion = ecs::entity::Entity::getId();
					//ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
					ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
					ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/Explosion", 12, ecs::core::Vector2<float>(70,70));
               		ecs::Ecs::deleteId(other);
               		ecs::Ecs::deleteId(self);
					t.addEvent(500, Time::MilliSeconds, [explosion](){ecs::Ecs::deleteId(explosion);});
				}
        	});
			m.addEvent(2, Time::Seconds, [bullet](){ecs::Ecs::deleteId(bullet);});
			ecs::Ecs::getComponentMap<game::Firerate>()[id]._lastfire = std::chrono::system_clock::now();
	}

	void Fire::shoot(ID id) {
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - ecs::Ecs::getComponentMap<game::Firerate>()[id]._lastfire).count() > ecs::Ecs::getComponentMap<game::Firerate>()[id]._firerate) {
		if (ecs::Ecs::idHasComponents<game::component::Inventory>(id)) {
			if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire == 0) {
				shootFire(id, 10, 0);
			} else if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire == 1) {
				shootFire(id, cosf(-2 * M_PI / 180) * 10, sinf(-2 * M_PI / 180) * 10);
				shootFire(id, cosf(2 * M_PI / 180) * 10, sinf(2 * M_PI / 180) * 10);
			} else if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire == 2) {
				shootFire(id, 10, 0);
				shootFire(id, cosf(-3 * M_PI / 180) * 10, sinf(-3 * M_PI / 180) * 10);
				shootFire(id, cosf(3 * M_PI / 180) * 10, sinf(3 * M_PI / 180) * 10);
			} else if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire == 3) {
				shootFire(id, cosf(-4 * M_PI / 180) * 10, sinf(-4 * M_PI / 180) * 10);
				shootFire(id, cosf(4 * M_PI / 180) * 10, sinf(4 * M_PI / 180) * 10);
				shootFire(id, cosf(-2 * M_PI / 180) * 10, sinf(-2 * M_PI / 180) * 10);
				shootFire(id, cosf(2 * M_PI / 180) * 10, sinf(2 * M_PI / 180) * 10);
			} else if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire >= 4) {
				shootFire(id, 10, 0);
				shootFire(id, cosf(-3 * M_PI / 180) * 10, sinf(-3 * M_PI / 180) * 10);
				shootFire(id, cosf(3 * M_PI / 180) * 10, sinf(3 * M_PI / 180) * 10);
				shootFire(id, cosf(-5 * M_PI / 180) * 10, sinf(-5 * M_PI / 180) * 10);
				shootFire(id, cosf(5 * M_PI / 180) * 10, sinf(5 * M_PI / 180) * 10);
			}
		}
		}
	}
}}