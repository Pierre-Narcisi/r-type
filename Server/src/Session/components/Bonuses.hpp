//
// Created by pierre on 20/11/2018.
//

#pragma once

#define NOSPRITE
#include <random>
#include "Session/TimedEvent/TimedEventAdmin.hpp"
#include "component/physic/Speed.hpp"
#include "component/physic/Position.hpp"
#include "component/physic/Hitbox.hpp"
#include "component/online/OnlineComponent.hpp"
#include "Session/components/Inventory.hpp"
#include "Session/components/Types.hpp"
#include "ecs/Ecs.hpp"
#include "Session/Session.hpp"
#undef NOSPRITE

namespace game { namespace component{
    struct Bonuses {
		Bonuses() {}
		Bonuses(ID id, rtype::session::Session &session):
			_id(id), _session(&session) {}
		~Bonuses() {
			TimedEventAdmin	m;

			auto *s = _session;
			auto x = this->x;
			auto y = this->y; 

			m.addEvent(500, Time::MilliSeconds, std::function<void()>([s, x, y] {
				std::random_device generator;
				std::uniform_int_distribution<int> distribution(1, 25);
				int my_rand = distribution(generator);
				if (my_rand == 10) {
					ID bonus = ecs::entity::Entity::getId();
					ecs::Ecs::addComponent<ecs::component::Position>(bonus, x, y);
					ecs::Ecs::addComponent<ecs::component::Speed>(bonus, -1, 0);
					ecs::Ecs::addComponent<game::component::Type>(bonus, game::component::Type::Types::BONUS);
					//ecs::Ecs::addComponent<ecs::component::Drawable>(bonus, 0, true);
					//ecs::Ecs::addComponent<ecs::component::Sprite>(bonus, "assets/Sprite/Becs::Ecs::addComponent<game::component::Type>(_id, game::component::Type::Types::BULLET_ENEMY);onuses/bonuses1.png", ecs::core::Vector2<float>(64, 32));
					ecs::Ecs::addComponent<ecs::component::OnlineComponent>(bonus, bonus, proto::SpriteId::BONUS);
					auto sessionPtr = s;
					ecs::Ecs::addComponent<ecs::component::Hitbox>(bonus, 64.f, 32.f, false, [sessionPtr, bonus](ID self, ID other){
						game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
						if (type._type == game::component::Type::Types::SHIP) {
							proto::Delete	pack{proto::Type::DELETE, sessionPtr->getId(), 0, self};

							ecs::Ecs::getComponentMap<game::component::Inventory>()[other]._fire++;
							ecs::Ecs::deleteLater(self);	
							sessionPtr->sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
						}
					});
					s->sendCreate(bonus);
				}
			}));
		}
		ID _id;
		float x;
		float y;
		rtype::session::Session *_session;
    };
}}