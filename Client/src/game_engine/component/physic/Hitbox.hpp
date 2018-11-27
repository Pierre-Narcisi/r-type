/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#pragma once

#include <functional>
#include <core/CoreVector.hpp>
#include "ecs/Entity.hpp"
#include "component/graphical/Sprite.hpp"
#include "component/graphical/AnimatedSprite.hpp"
#include "component/graphical/AnimatedSpriteMap.hpp"
#include "ecs/Ecs.hpp"

namespace ecs {namespace component {
	struct Hitbox {
		Hitbox() {}
		Hitbox(ID id) {
			this->collidable = false;
			if (ecs::Ecs::idHasComponents<component::Sprite>(id)) {
				this->height = ecs::Ecs::getComponentMap<Sprite>()[id].boxSize.x / 2;
				this->width = ecs::Ecs::getComponentMap<Sprite>()[id].boxSize.x / 2;
			} else if (ecs::Ecs::idHasComponents<component::AnimatedSprite>(id)) {
				this->height = ecs::Ecs::getComponentMap<AnimatedSprite>()[id].boxSize.x / 2;
				this->width = ecs::Ecs::getComponentMap<AnimatedSprite>()[id].boxSize.x / 2;
			} else if (ecs::Ecs::idHasComponents<component::AnimatedSpriteMap>(id)) {
				this->height = ecs::Ecs::getComponentMap<AnimatedSpriteMap>()[id].boxSize.x / 2;
				this->width = ecs::Ecs::getComponentMap<AnimatedSpriteMap>()[id].boxSize.x / 2;
			}
		}
		Hitbox(ID id, bool collidable) {
			this->collidable = collidable;
			if (ecs::Ecs::idHasComponents<component::Sprite>(id)) {
				this->height = ecs::Ecs::getComponentMap<Sprite>()[id].boxSize.x / 2;
				this->width = ecs::Ecs::getComponentMap<Sprite>()[id].boxSize.x / 2;
			} else if (ecs::Ecs::idHasComponents<component::AnimatedSprite>(id)) {
				this->height = ecs::Ecs::getComponentMap<AnimatedSprite>()[id].boxSize.x / 2;
				this->width = ecs::Ecs::getComponentMap<AnimatedSprite>()[id].boxSize.x / 2;
			} else if (ecs::Ecs::idHasComponents<component::AnimatedSpriteMap>(id)) {
				this->height = ecs::Ecs::getComponentMap<AnimatedSpriteMap>()[id].boxSize.x / 2;
				this->width = ecs::Ecs::getComponentMap<AnimatedSpriteMap>()[id].boxSize.x / 2;
			}
		}
		Hitbox(ID id, std::function<void(ID,ID)> function) {
			this->func = function;
			this->collidable = false;
			if (ecs::Ecs::idHasComponents<component::Sprite>(id)) {
				this->width = ecs::Ecs::getComponentMap<Sprite>()[id].boxSize.x / 2;
				this->height = ecs::Ecs::getComponentMap<Sprite>()[id].boxSize.x / 2;
			} else if (ecs::Ecs::idHasComponents<component::AnimatedSprite>(id)) {
				this->width = ecs::Ecs::getComponentMap<AnimatedSprite>()[id].boxSize.x / 2;
				this->height = ecs::Ecs::getComponentMap<AnimatedSprite>()[id].boxSize.x / 2;
			} else if (ecs::Ecs::idHasComponents<component::AnimatedSpriteMap>(id)) {
				this->width = ecs::Ecs::getComponentMap<AnimatedSpriteMap>()[id].boxSize.x / 2;
				this->height = ecs::Ecs::getComponentMap<AnimatedSpriteMap>()[id].boxSize.x / 2;
			}
		}
		Hitbox(ID id, bool collidable, std::function<void(ID,ID)> function) {
			this->func = function;
			this->collidable = collidable;
			if (ecs::Ecs::idHasComponents<component::Sprite>(id)) {
				this->width = ecs::Ecs::getComponentMap<Sprite>()[id].boxSize.x / 2;
				this->height = ecs::Ecs::getComponentMap<Sprite>()[id].boxSize.x / 2;
			} else if (ecs::Ecs::idHasComponents<component::AnimatedSprite>(id)) {
				this->width = ecs::Ecs::getComponentMap<AnimatedSprite>()[id].boxSize.x / 2;
				this->height = ecs::Ecs::getComponentMap<AnimatedSprite>()[id].boxSize.x / 2;
			} else if (ecs::Ecs::idHasComponents<component::AnimatedSpriteMap>(id)) {
				this->width = ecs::Ecs::getComponentMap<AnimatedSpriteMap>()[id].boxSize.x / 2;
				this->height = ecs::Ecs::getComponentMap<AnimatedSpriteMap>()[id].boxSize.x / 2;
			}
		}
		Hitbox(float width, float height) {
			this->width = width / 2;
			this->height = height / 2;
			this->collidable = false;
		}
		Hitbox(float width, float height, bool collidable) {
			this->width = width / 2;
			this->height = height / 2;
			this->collidable = collidable;
		}
		Hitbox(float width, float height, bool collidable, std::function<void(ID, ID)> function) {
			this->width = width / 2;
			this->height = height / 2;
			this->func = function;
			this->collidable = collidable;
		}
		float				height;
		float				width;
		std::function<void(ID, ID)>	func;
		bool 				collidable;
	};
}}