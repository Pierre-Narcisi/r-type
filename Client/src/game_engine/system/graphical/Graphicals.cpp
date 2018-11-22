/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include <component/graphical/AnimatedSpriteMap.hpp>
#include <component/graphical/Drawable.hpp>
#include "component/graphical/Sprite.hpp"
#include "component/physic/Position.hpp"
#include "ecs/Ecs.hpp"
#include "core/Time.hpp"
#include "Graphicals.hpp"

namespace ecs {namespace system {
	void Graphicals::UpdateGraphicals() {
		auto drawableIds = Ecs::filter<ecs::component::Drawable, ecs::component::Position>();

		auto &drawables = Ecs::getConponentMap<component::Drawable>();
		auto &sprites = Ecs::getConponentMap<component::Sprite>();
		auto &positions = Ecs::getConponentMap<component::Position>();
		auto &animateds = Ecs::getConponentMap<component::AnimatedSprite>();
		auto &animatedmaps = Ecs::getConponentMap<component::AnimatedSpriteMap>();

		auto window = graphical::Graphic::getWindow();

		for (auto id = drawableIds.begin(); id != drawableIds.end(); id++) {
			if (!drawables[*id].visible) {
				drawableIds.erase(id);
				if (id != drawableIds.begin())
					id--;
			}
		}
		std::sort (drawableIds.begin(), drawableIds.end(), [](ID one, ID two){ return (
			Ecs::getConponentMap<component::Drawable>()[one].layer <
				Ecs::getConponentMap<component::Drawable>()[two].layer); });

		for (auto id : drawableIds) {
			if (Ecs::idHasComponents<component::Sprite>(id)) {
				sprites[id].sprite->setPosition(positions[id].x, positions[id].y);
				window->draw(*sprites[id].sprite);
			}
			if (Ecs::idHasComponents<component::AnimatedSprite>(id)) {
				UpdateAnimatedSprite(animateds[id]);
				animateds[id].animation[animateds[id].frame].sprite->setPosition(positions[id].x, positions[id].y);
				window->draw(*animateds[id].animation[animateds[id].frame].sprite);
			}
			if (Ecs::idHasComponents<component::AnimatedSpriteMap>(id)) {
				UpdateAnimatedSprite(animatedmaps[id].animatedSprites[animatedmaps[id].pos]);
				animatedmaps[id].animatedSprites[animatedmaps[id].pos].animation[animatedmaps[id].animatedSprites[animatedmaps[id].pos].frame].sprite->setPosition(positions[id].x, positions[id].y);
				window->draw(*animatedmaps[id].animatedSprites[animatedmaps[id].pos].animation[animatedmaps[id].animatedSprites[animatedmaps[id].pos].frame].sprite);
			}
		}
	}

	void Graphicals::UpdateAnimatedSprite(component::AnimatedSprite &animated) {
		if (core::Time::get(TimeUnit::MicroSeconds) - animated.oldTime > animated.interFrame) {
			animated.frame = (animated.frame + 1) % animated.animation.size();
			animated.oldTime = core::Time::get(TimeUnit::MicroSeconds);
		}
	}
}}