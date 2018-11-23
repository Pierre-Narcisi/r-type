//
// Created by pierre on 20/11/2018.
//

#include "enemy1.hpp"

void enemy1::init(ID _id) {
	ecs::Ecs::addComponent<ecs::component::Drawable>(_id, 1, true);	
	ecs::Ecs::addComponent<ecs::component::Position>(_id, 1000.f, 150.f);
	ecs::Ecs::addComponent<ecs::component::Hitbox>(_id, 100, 100, true);
	ecs::Ecs::addComponent<ecs::component::Speed>(_id, -0.5f, 0.f);
	ecs::Ecs::addComponent<ecs::component::AnimatedSprite>(_id, "./assets", 4);
}

void enemy1::update(ID _id) {
}