//
// Created by pierre on 27/11/2018.
//

#include <random>
#include "walls.hpp"

namespace game {namespace system {
		void walls::updateDown() {
			if (_bindDown == (unsigned long)-1) {
				_bindDown = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<game::component::Type>(_bindDown, game::component::Type::Types::WALL);
				ecs::Ecs::addComponent<ecs::component::Drawable>(_bindDown, 1, true);
				ecs::Ecs::addComponent<ecs::component::Sprite>(_bindDown, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["Sprite/Walls/Wall1.png"], "Sprite/Walls/Wall1.png", ecs::core::Vector2<float>(192, 96));
				ecs::Ecs::addComponent<ecs::component::Hitbox>(_bindDown, _bindDown, true, true/*, [](ID self, ID other){if (!ecs::Ecs::idHasComponents<game::component::wall>(other)){ecs::Ecs::deleteId(other);}}*/);
				int x = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindDown].size.x;
				int y = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindDown].size.y;
				ecs::Ecs::addComponent<game::component::wall>(_bindDown);
				ecs::Ecs::addComponent<ecs::component::Position>(_bindDown, 1280 + x / 2, 720 - y / 2);
				ecs::Ecs::addComponent<ecs::component::Speed>(_bindDown, -0.5f, 0.f);
			} else if (ecs::Ecs::getComponentMap<ecs::component::Position>()[_bindDown].x < 1280) {
				std::random_device generator;
				std::uniform_int_distribution<int> distribution(1, 8);
				int nb = distribution(generator);
				int oldSizeX = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindDown].size.x;
				int oldPosX = ecs::Ecs::getComponentMap<ecs::component::Position>()[_bindDown].x;
				_bindDown = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<game::component::Type>(_bindDown, game::component::Type::Types::WALL);
				ecs::Ecs::addComponent<ecs::component::Drawable>(_bindDown, 1, true);
				ecs::Ecs::addComponent<game::component::wall>(_bindDown);
				ecs::Ecs::addComponent<ecs::component::Sprite>(_bindDown, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()[_wallList[nb].first], _wallList[nb].first, _wallList[nb].second);
				ecs::Ecs::addComponent<ecs::component::Hitbox>(_bindDown, _bindDown, true, true/*, [](ID self, ID other){if (!ecs::Ecs::idHasComponents<game::component::wall>(other)){ecs::Ecs::deleteId(other);}}*/);
				int x = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindDown].size.x;
				int y = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindDown].size.y;
				ecs::Ecs::addComponent<ecs::component::Position>(_bindDown, oldPosX + oldSizeX / 2 + x / 2, 720 - y / 2);
				ecs::Ecs::addComponent<ecs::component::Speed>(_bindDown, -0.5f, 0.f);
			}
		}
		void walls::updateUp() {
			if (_bindUp == (unsigned long)-1) {
				_bindUp = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<game::component::Type>(_bindUp, game::component::Type::Types::WALL);
				ecs::Ecs::addComponent<game::component::wall>(_bindUp);
				ecs::Ecs::addComponent<ecs::component::Drawable>(_bindUp, 1, true);
				ecs::Ecs::addComponent<ecs::component::Sprite>(_bindUp, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()["Sprite/WallsRotate/Wall1.png"], "Sprite/WallsRotate/Wall1.png", ecs::core::Vector2<float>(192, 96));
				ecs::Ecs::addComponent<ecs::component::Hitbox>(_bindUp, _bindUp, true, true/*, [](ID self, ID other){if (!ecs::Ecs::idHasComponents<game::component::wall>(other)){ecs::Ecs::deleteId(other);}}*/);
				int x = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindUp].size.x;
				int y = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindUp].size.y;
				ecs::Ecs::addComponent<ecs::component::Position>(_bindUp, 1280 + x / 2, 0 + y / 2);
				ecs::Ecs::addComponent<ecs::component::Speed>(_bindUp, -0.5f, 0.f);
			} else if (ecs::Ecs::getComponentMap<ecs::component::Position>()[_bindUp].x < 1280) {
				std::random_device generator;
				std::uniform_int_distribution<int> distribution(9, 16);
				int nb = distribution(generator);
				int oldSizeX = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindUp].size.x;
				int oldPosX = ecs::Ecs::getComponentMap<ecs::component::Position>()[_bindUp].x;
				_bindUp = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<game::component::Type>(_bindUp, game::component::Type::Types::WALL);
				ecs::Ecs::addComponent<game::component::wall>(_bindUp);
				ecs::Ecs::addComponent<ecs::component::Drawable>(_bindUp, 1, true);
				ecs::Ecs::addComponent<ecs::component::Sprite>(_bindUp, ecs::DataBank<std::string, ecs::graphical::BundleSprite>::get()[_wallList[nb].first], _wallList[nb].first, _wallList[nb].second);
				ecs::Ecs::addComponent<ecs::component::Hitbox>(_bindUp, _bindUp, true, true/*, [](ID self, ID other){if (!ecs::Ecs::idHasComponents<game::component::wall>(other)){ecs::Ecs::deleteId(other);}}*/);
				int x = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindUp].size.x;
				int y = ecs::Ecs::getComponentMap<ecs::component::Sprite>()[_bindUp].size.y;
				ecs::Ecs::addComponent<ecs::component::Position>(_bindUp, oldPosX + oldSizeX / 2 + x / 2, 0 + y / 2);
				ecs::Ecs::addComponent<ecs::component::Speed>(_bindUp, -0.5f, 0.f);
			}
		}

		void walls::updateWalls() {
			auto ids = ecs::Ecs::filter<game::component::wall>();
			auto wallPos = ecs::Ecs::getComponentMap<ecs::component::Position>();

			for (auto id: ids) {
				if (wallPos[id].x + ecs::Ecs::getComponentMap<ecs::component::Sprite>()[id].size.x / 2 <  0) {
					ecs::Ecs::deleteId(id);
				}
			}
			updateDown();
			updateUp();
		}
	}}
