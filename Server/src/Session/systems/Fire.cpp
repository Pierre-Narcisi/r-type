//
// Created by pierre on 20/11/2018.
//
#define NOSPRITE
#define _USE_MATH_DEFINES
#include <cmath>
#include "component/online/OnlineComponent.hpp"
#include "Session/components/Inventory.hpp"
#include "ecs/Ecs.hpp"
#include "component/physic/Position.hpp"
#include "component/physic/Speed.hpp"
#include "component/physic/Hitbox.hpp"
#include "core/Time.hpp"
#include "lib/TimedEvent/TimedEventAdmin.hpp"
#include "Session/components/Types.hpp"
#include "Session/components/Firerate.hpp"
#include "ecs/DataBank.hpp"
#include "Fire.hpp"
#undef NOSPRITE

namespace game { namespace system {

void Fire::shootFire(ID id, float spX, float spY, rtype::session::Session &session) {
	TimedEventAdmin m;
	ID bullet = ecs::entity::Entity::getId();
	ecs::Ecs::addComponent<ecs::component::Speed>(bullet, spX, spY);
	//ecs::Ecs::addComponent<ecs::component::Drawable>(bullet, 1, true);
	ecs::Ecs::addComponent<game::component::Type>(bullet, game::component::Type::Types::BULLET_SHIP);
	ecs::Ecs::addComponent<ecs::component::OnlineComponent>(bullet, bullet, proto::SpriteId::BULLET3);
	ecs::Ecs::addComponent<ecs::component::Position>(bullet, ecs::Ecs::getComponentMap<ecs::component::Position>()[id].x + 1, ecs::Ecs::getComponentMap<ecs::component::Position>()[id].y);
	//ecs::Ecs::addComponent<ecs::component::Sprite>(bullet, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["assets/Sprite/ClassicBullet/ClassicBullet3.png"], "assets/Sprite/ClassicBullet/ClassicBullet3.png");
	ecs::Ecs::addComponent<ecs::component::Hitbox>(bullet, 15.f, 15.f, false, [id, &session](ID self, ID other) {
		game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
		if (type._type == game::component::Type::Types::BULLET_ENEMY || type._type == game::component::Type::Types::ENEMY) {
			TimedEventAdmin t;
			ID explosion = ecs::entity::Entity::getId();
			//ecs::Ecs::addComponent<ecs::component::Drawable>(explosion, 1, true);
			ecs::Ecs::addComponent<ecs::component::Position>(explosion, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].x, ecs::Ecs::getComponentMap<ecs::component::Position>()[other].y);
			ecs::Ecs::addComponent<ecs::component::Hitbox>(explosion, 64, 64);
			//ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(explosion, "assets/Sprite/Explosion", 12, ecs::core::Vector2<float>(70,70));
			ecs::Ecs::addComponent<ecs::component::OnlineComponent>(explosion, explosion, proto::SpriteId::EXPLOSION);
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
	});
	m.addEvent(2, Time::Seconds, [bullet, &session](){
		ecs::Ecs::deleteId(bullet);

		proto::Delete	pack{proto::Type::DELETE, session.getId(), 0, bullet};
		session.sendToPlayers(reinterpret_cast<proto::PacketBase&>(pack), sizeof(pack));
	});
	session.sendCreate(bullet);
	ecs::Ecs::getComponentMap<game::Firerate>()[id]._lastfire = std::chrono::system_clock::now();
}

void Fire::shoot(ID id, rtype::session::Session &session) {
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - ecs::Ecs::getComponentMap<game::Firerate>()[id]._lastfire).count() > ecs::Ecs::getComponentMap<game::Firerate>()[id]._firerate) {
	if (ecs::Ecs::idHasComponents<game::component::Inventory>(id)) {
		if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire == 0) {
			shootFire(id, 10.f, 0.f, session);
		} else if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire == 1) {
			shootFire(id, cosf(-2.f * M_PI / 180.f) * 10.f, sinf(-2.f * M_PI / 180.f) * 10.f, session);
			shootFire(id, cosf(2.f * M_PI / 180.f) * 10.f, sinf(2.f * M_PI / 180.f) * 10.f, session);
		} else if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire == 2) {
			shootFire(id, 10, 0, session);
			shootFire(id, cosf(-3.f * M_PI / 180.f) * 10.f, sinf(-3.f * M_PI / 180.f) * 10.f, session);
			shootFire(id, cosf(3.f * M_PI / 180.f) * 10.f, sinf(3.f * M_PI / 180.f) * 10.f, session);
		} else if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire == 3) {
			shootFire(id, cosf(-4.f * M_PI / 180.f) * 10.f, sinf(-4.f * M_PI / 180.f) * 10.f, session);
			shootFire(id, cosf(4.f * M_PI / 180.f) * 10.f, sinf(4.f * M_PI / 180.f) * 10.f, session);
			shootFire(id, cosf(-2.f * M_PI / 180.f) * 10.f, sinf(-2.f * M_PI / 180.f) * 10.f, session);
			shootFire(id, cosf(2.f * M_PI / 180.f) * 10.f, sinf(2.f * M_PI / 180.f) * 10.f, session);
		} else if (ecs::Ecs::getComponentMap<game::component::Inventory>()[id]._fire >= 4) {
			shootFire(id, 10, 0, session);
			shootFire(id, cosf(-3.f * M_PI / 180.f) * 10.f, sinf(-3.f * M_PI / 180.f) * 10.f, session);
			shootFire(id, cosf(3.f * M_PI / 180.f) * 10.f, sinf(3.f * M_PI / 180.f) * 10.f, session);
			shootFire(id, cosf(-5.f * M_PI / 180.f) * 10.f, sinf(-5.f * M_PI / 180.f) * 10.f, session);
			shootFire(id, cosf(5.f * M_PI / 180.f) * 10.f, sinf(5.f * M_PI / 180.f) * 10.f, session);
		}
	}
	}
}

}}