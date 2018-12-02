//
// Created by pierre on 20/11/2018.
//

#include "enemy3.hpp"
#include "math.h"

#define NOSPRITE
#include "component/physic/Position.hpp"
#include "component/physic/Speed.hpp"
#include "component/physic/Acceleration.hpp"
#include "component/physic/Hitbox.hpp"
#include "component/online/OnlineComponent.hpp"
#include "core/Time.hpp"
#include "Session/TimedEvent/TimedEventAdmin.hpp"
#include "ecs/Ecs.hpp"
//#include "component/Bonuses.hpp"
#include "ecs/DataBank.hpp"
#include "Session/components/Types.hpp"
//#include "system/walls.hpp"
#include "enemy3.hpp"
#include "math.h"
#undef NOSPRITE

namespace game {
	void enemy3::init(ID _id, int posx, int posy, rtype::session::Session &session) {
		_time = ecs::core::Time::get(TimeUnit::Seconds);
		ecs::Ecs::addComponent<game::component::Type>(_id, game::component::Type::Types::ENEMY);
		//ecs::Ecs::addComponent<ecs::component::Drawable>(_id, 1, true);	
		//ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(_id, "assets/Sprite/Enemy3/", 8, ecs::core::Vector2<float>(40, 40));
		ecs::Ecs::addComponent<ecs::component::Position>(_id, posx, posy);
		//ecs::Ecs::addComponent<game::component::Bonuses>(_id, _id);
		ecs::Ecs::addComponent<ecs::component::Speed>(_id, -1.f, 0.f);
		ecs::Ecs::addComponent<ecs::component::OnlineComponent>(_id, _id, proto::SpriteId::ENEMY3);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(_id, 40.f, 40.f, false, static_cast<std::function<void(ID, ID)>>([&session](ID self, ID other){
			game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
			if (type._type == game::component::Type::Types::SHIP) {
				TimedEventAdmin t;
				ID explosion = ecs::entity::Entity::getId();
				//ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
				ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
				//ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/BigExplosion", 10, ecs::core::Vector2<float>(70,70));
				ecs::Ecs::addComponent<ecs::component::OnlineComponent>(explosion, explosion, proto::SpriteId::BIG_EXPLOSION);
				ecs::Ecs::addComponent<ecs::component::Hitbox>(explosion, 64, 64);
				ecs::Ecs::deleteId(other);
				ecs::Ecs::deleteId(self);

				auto onDestroy = [explosion, &session](){
					ecs::Ecs::deleteId(explosion);

						proto::Delete	pack{proto::Type::DELETE, session.getId(), 0, explosion};

						session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
				};

				proto::Delete	packo{proto::Type::DELETE, session.getId(), 0, other};
				proto::Delete	packs{proto::Type::DELETE, session.getId(), 0, self};

				session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(packo), sizeof(packo));
				session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(packs), sizeof(packs));

				session.sendCreate(explosion);
				t.addEvent(1000, Time::MilliSeconds, [onDestroy]{ onDestroy(); });
			}
		}));
	}

	void enemy3::update(ID _id, rtype::session::Session &session) {
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto &speed = ecs::Ecs::getComponentMap<ecs::component::Speed>();
		auto ship = ecs::Ecs::filter<ecs::component::Keyboard>();
		float dist;
		float res_dist = -1;
		ID res;

		if (pos[_id].x < 1000) {
			speed[_id].x = 0;
			if (pos[_id].y > 600)
				speed[_id].y = -0.5;
			else if (pos[_id].y < 200)
				speed[_id].y = 0.5;
			else if (speed[_id].y == 0)
				speed[_id].y = -0.5;
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
			float v1 = (pos[_id].x - pos[res].x);
			float v2 = (pos[_id].y - pos[res].y);
			double angle = std::atan2(-v1, -v2);
			ID bullet = ecs::entity::Entity::getId();
			ecs::Ecs::addComponent<ecs::component::Speed>(bullet, sinf(angle) * 7, cosf(angle) * 7);
			ecs::Ecs::addComponent<game::component::Type>(_id, game::component::Type::Types::BULLET_ENEMY);
			//ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 1, true);
			ecs::Ecs::addComponent<ecs::component::Position>(bullet, ecs::Ecs::getComponentMap<ecs::component::Position>()[_id].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[_id].y);
			//ecs::Ecs::addComponent<ecs::component::Sprite>(bullet, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["assets/Sprite/ClassicBullet/ClassicBullet2.png"], "assets/Sprite/ClassicBullet/ClassicBullet3.png", ecs::core::Vector2<float>(30, 30));
			ecs::Ecs::addComponent<ecs::component::OnlineComponent>(bullet, bullet, proto::SpriteId::BULLET2);
			ecs::Ecs::addComponent<game::component::Type>(_id, game::component::Type::Types::BULLET_ENEMY);
			ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, 15.f, 15.f, false, [_id, &session](ID self, ID other){
				game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
				if (type._type == game::component::Type::Types::SHIP || type._type == game::component::Type::Types::BULLET_SHIP) {
					TimedEventAdmin t;
					ID explosion = ecs::entity::Entity::getId();
					//ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
					ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
					//ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/BigExplosion", 10, ecs::core::Vector2<float>(70,70));
					ecs::Ecs::addComponent<ecs::component::OnlineComponent>(explosion, explosion, proto::SpriteId::BIG_EXPLOSION);
					ecs::Ecs::addComponent<ecs::component::Hitbox>(explosion, 64, 64);
					ecs::Ecs::deleteId(other);
					ecs::Ecs::deleteId(self);

					auto onDestroy = [explosion, &session](){
						ecs::Ecs::deleteId(explosion);

							proto::Delete	pack{proto::Type::DELETE, session.getId(), 0, explosion};

							session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
						
					};

					proto::Delete	packo{proto::Type::DELETE, session.getId(), 0, other};
					proto::Delete	packs{proto::Type::DELETE, session.getId(), 0, self};

					session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(packo), sizeof(packo));
					session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(packs), sizeof(packs));

					session.sendCreate(explosion);
					t.addEvent(1000, Time::MilliSeconds, [onDestroy]{ onDestroy(); });
				}
        	});
			session.sendCreate(bullet);
			m.addEvent(5, Time::Seconds, [bullet, &session](){
				ecs::Ecs::deleteId(bullet);

				proto::Delete	pack{proto::Type::DELETE, session.getId(), 0, bullet};

				session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
			});
		}
	}
}