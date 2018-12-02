//
// Created by pierre on 20/11/2018.
//

#define NOSPRITE
#include "Session/components/Types.hpp"
//#include "component/Bonuses.hpp"
#include "component/physic/Position.hpp"
//#include "component/graphical/AnimatedSprite.hpp"
#include "component/online/OnlineComponent.hpp"
#include "component/physic/Speed.hpp"
#include "component/physic/Hitbox.hpp"
#include "core/Time.hpp"
#include "lib/TimedEvent/TimedEventAdmin.hpp"
#include "enemy1.hpp"
#include "Network/GameProtocol.hpp"
#include "math.h"
#undef NOSPRITE


namespace game {
	void enemy1::init(ID _id, int posx, int posy, rtype::session::Session &session) {
		std::cout << "Create Enemy!!" << std::endl;
		_time = ecs::core::Time::get(TimeUnit::Seconds);
		//ecs::Ecs::addComponent<ecs::component::Drawable>(_id, 1, true);
		ecs::Ecs::addComponent<game::component::Type>(_id, game::component::Type::Types::ENEMY);
		//ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(_id, "assets/Sprite/Enemy1/", 4, ecs::core::Vector2<float>(40, 40));
		ecs::Ecs::addComponent<ecs::component::Position>(_id, posx, posy);
		ecs::Ecs::addComponent<ecs::component::Speed>(_id, -3.f, 0.f);
		//ecs::Ecs::addComponent<game::component::Bonuses>(_id, _id);
		ecs::Ecs::addComponent<ecs::component::OnlineComponent>(_id, _id, proto::SpriteId::ENEMY1);
		ecs::Ecs::addComponent<ecs::component::Hitbox>(_id, 40, 40, false, static_cast<std::function<void(ID, ID)>>([&session](ID self, ID other){
			game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
			if (type._type == game::component::Type::Types::SHIP) {
				TimedEventAdmin t;
				ID explosion = ecs::entity::Entity::getId();
				//ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
				ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
				ecs::Ecs::addComponent<ecs::component::Hitbox>(explosion, 64, 64);
				ecs::Ecs::addComponent<ecs::component::OnlineComponent>(explosion, explosion, proto::SpriteId::BIG_EXPLOSION);
				//ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/BigExplosion", 10, ecs::core::Vector2<float>(70,70));
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
				t.addEvent(500, Time::MilliSeconds, [onDestroy]{ onDestroy(); });
			}
		}));
	}

	void enemy1::update(ID _id, rtype::session::Session &session) {
		auto &pos = ecs::Ecs::getComponentMap<ecs::component::Position>();
		auto &speed = ecs::Ecs::getComponentMap<ecs::component::Speed>();

		speed[_id].y = sin(pos[_id].x / 70);
		if (pos[_id].x < 0) {
			ecs::Ecs::deleteId(_id);

			proto::Delete	pack{proto::Type::DELETE, session.getId(), 0, _id};
			session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
		}
	}
}
