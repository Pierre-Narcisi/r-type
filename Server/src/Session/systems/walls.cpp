//
// Created by pierre on 27/11/2018.
//

#include <random>
#include "walls.hpp"
#include "component/online/OnlineComponent.hpp"

namespace game {namespace system {
		void walls::updateDown(rtype::session::Session &session) {
			if (_bindDown == (unsigned long)-1) {
				_bindDown = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<game::component::Type>(_bindDown, game::component::Type::Types::WALL);
				//ecs::Ecs::addComponent<ecs::component::Drawable>(_bindDown, 1, true);
				//ecs::Ecs::addComponent<ecs::component::Sprite>(_bindDown, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["assets/Sprite/Walls/Wall1.png"], "assets/Sprite/Walls/Wall1.png", ecs::core::Vector2<float>(192, 96));
				ecs::Ecs::addComponent<ecs::component::OnlineComponent>(_bindDown, _bindDown, proto::SpriteId::WALL1);
				float x = _wallList[0].second.x;
				float y = _wallList[0].second.y;
				ecs::Ecs::addComponent<ecs::component::Hitbox>(_bindDown, x, y, false, true/*, [](ID self, ID other){if (!ecs::Ecs::idHasComponents<game::component::wall>(other)){ecs::Ecs::deleteLater(other);}}*/);
				ecs::Ecs::addComponent<game::component::wall>(_bindDown);
				ecs::Ecs::addComponent<ecs::component::Position>(_bindDown, 1280 + x / 2, 720 - y / 2);
				ecs::Ecs::addComponent<ecs::component::Speed>(_bindDown, -0.5f, 0.f);
				ecs::Ecs::addComponent<ecs::component::OnlineComponent>(_bindDown, _bindDown, _wallList[0].first);
				session.sendCreate(_bindDown);
			} else if (ecs::Ecs::getComponentMap<ecs::component::Position>()[_bindDown].x < 1280) {
				std::random_device generator;
				std::uniform_int_distribution<int> distribution(0, 7);
				int nb = distribution(generator);
				float oldSizeX = ecs::Ecs::getComponentMap<ecs::component::Hitbox>()[_bindDown].width;
				float oldPosX = ecs::Ecs::getComponentMap<ecs::component::Position>()[_bindDown].x;
				_bindDown = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<game::component::Type>(_bindDown, game::component::Type::Types::WALL);
				//ecs::Ecs::addComponent<ecs::component::Drawable>(_bindDown, 1, true);
				ecs::Ecs::addComponent<game::component::wall>(_bindDown);
				//ecs::Ecs::addComponent<ecs::component::Sprite>(_bindDown, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()[_wallList[nb].first], _wallList[nb].first, _wallList[nb].second);
				float x = _wallList[nb].second.x;
				float y = _wallList[nb].second.y;
				ecs::Ecs::addComponent<ecs::component::Hitbox>(_bindDown, x, y, false, true/*, [](ID self, ID other){if (!ecs::Ecs::idHasComponents<game::component::wall>(other)){ecs::Ecs::deleteLater(other);}}*/);
				ecs::Ecs::addComponent<ecs::component::Position>(_bindDown, oldPosX + oldSizeX + x / 2, 720 - y / 2);
				ecs::Ecs::addComponent<ecs::component::Speed>(_bindDown, -0.5f, 0.f);
				ecs::Ecs::addComponent<ecs::component::OnlineComponent>(_bindDown, _bindDown, _wallList[nb].first);
				session.sendCreate(_bindDown);
			}
		}
		void walls::updateUp(rtype::session::Session &session) {
			if (_bindUp == (unsigned long)-1) {
				_bindUp = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<game::component::Type>(_bindUp, game::component::Type::Types::WALL);
				ecs::Ecs::addComponent<game::component::wall>(_bindUp);
				ecs::Ecs::addComponent<ecs::component::OnlineComponent>(_bindUp, _bindUp, proto::SpriteId::WALL_ROTATE1);
				//ecs::Ecs::addComponent<ecs::component::Drawable>(_bindUp, 1, true);
				//ecs::Ecs::addComponent<ecs::component::Sprite>(_bindUp, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["assets/Sprite/WallsRotate/Wall1.png"], "assets/Sprite/WallsRotate/Wall1.png", ecs::core::Vector2<float>(192, 96));
				float x = _wallList[9].second.x;
				float y = _wallList[9].second.y;
				ecs::Ecs::addComponent<ecs::component::Hitbox>(_bindUp, x, y, false, true/*, [](ID self, ID other){if (!ecs::Ecs::idHasComponents<game::component::wall>(other)){ecs::Ecs::deleteLater(other);}}*/);
				ecs::Ecs::addComponent<ecs::component::Position>(_bindUp, 1280 + x / 2, 0 + y / 2);
				ecs::Ecs::addComponent<ecs::component::Speed>(_bindUp, -0.5f, 0.f);
				session.sendCreate(_bindUp);
			} else if (ecs::Ecs::getComponentMap<ecs::component::Position>()[_bindUp].x < 1280) {
				std::random_device generator;
				std::uniform_int_distribution<int> distribution(8, 15);
				int nb = distribution(generator);
				float oldSizeX = ecs::Ecs::getComponentMap<ecs::component::Hitbox>()[_bindUp].width;
				float oldPosX = ecs::Ecs::getComponentMap<ecs::component::Position>()[_bindUp].x;
				_bindUp = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<game::component::Type>(_bindUp, game::component::Type::Types::WALL);
				ecs::Ecs::addComponent<game::component::wall>(_bindUp);
				ecs::Ecs::addComponent<ecs::component::OnlineComponent>(_bindUp, _bindUp, _wallList[nb].first);
				//ecs::Ecs::addComponent<ecs::component::Drawable>(_bindUp, 1, true);
				//ecs::Ecs::addComponent<ecs::component::Sprite>(_bindUp, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()[_wallList[nb].first], _wallList[nb].first, _wallList[nb].second);
				float x = _wallList[nb].second.x;
				float y = _wallList[nb].second.y;
				ecs::Ecs::addComponent<ecs::component::Hitbox>(_bindUp, x, y, false, true/*, [](ID self, ID other){if (!ecs::Ecs::idHasComponents<game::component::wall>(other)){ecs::Ecs::deleteLater(other);}}*/);
				ecs::Ecs::addComponent<ecs::component::Position>(_bindUp, oldPosX + oldSizeX + x / 2, 0 + y / 2);
				ecs::Ecs::addComponent<ecs::component::Speed>(_bindUp, -0.5f, 0.f);
				session.sendCreate(_bindUp);
			}
		}

		void walls::updateWalls(rtype::session::Session &session) {
			auto ids = ecs::Ecs::filter<game::component::wall>();
			auto wallPos = ecs::Ecs::getComponentMap<ecs::component::Position>();

			for (auto id: ids) {
				if (wallPos[id].x + ecs::Ecs::getComponentMap<ecs::component::Hitbox>()[id].width <  0) {
					ecs::Ecs::deleteLater(id);
				}
			}
			updateDown(session);
			updateUp(session);
		}
	}}
