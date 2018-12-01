//
// Created by pierre on 20/11/2018.
//

#pragma once

#include "component/Inventory.hpp"
#include "component/physic/Speed.hpp"
#include "component/physic/Position.hpp"
#include "component/physic/Hitbox.hpp"
#include "component/graphical/Drawable.hpp"
#include "component/graphical/Sprite.hpp"
#include "component/Types.hpp"
#include "ecs/Ecs.hpp"
#include <random>

namespace game { namespace component{
    struct Bonuses {
		Bonuses() {
		}
        Bonuses(ID id) {
			_id = id;
		}
		~Bonuses() {
			std::random_device generator;
			std::uniform_int_distribution<int> distribution(1, 25);
			int my_rand = distribution(generator);
			if (my_rand == 10) {
				ID bonus = ecs::entity::Entity::getId();
				ecs::Ecs::addComponent<ecs::component::Position>(bonus, x, y);
				ecs::Ecs::addComponent<ecs::component::Speed>(bonus, -1, 0);
				ecs::Ecs::addComponent<game::component::Type>(bonus, game::component::Type::Types::BONUS);
				ecs::Ecs::addComponent<ecs::component::Drawable>(bonus, 0, true);
				ecs::Ecs::addComponent<ecs::component::Sprite>(bonus, "assets/Sprite/Bonuses/bonuses1.png", ecs::core::Vector2<float>(64, 32));
				ecs::Ecs::addComponent<ecs::component::Hitbox>(bonus, bonus, false, false, [bonus](ID self, ID other){
					game::component::Type type = ecs::Ecs::getComponentMap<game::component::Type>()[other];
					if (type._type == game::component::Type::Types::SHIP) {
						ecs::Ecs::getComponentMap<game::component::Inventory>()[other]._fire++;
						ecs::Ecs::deleteId(self);	
					}
				});
			}
		}
		ID _id;
		float x;
		float y;
    };
}}