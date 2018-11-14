/*
** EPITECH PROJECT, 2021
** rtype
** File description:
** Created by seb,
*/

#include "component/graphical/Sprite.hpp"
#include "component/physic/Position.hpp"
#include "ecs/Ecs.hpp"
#include "core/Time.hpp"
#include "Graphicals.hpp"

namespace ecs {namespace system {
	void Graphicals::UpdateGraphicals() {
		auto ids = Ecs::filter<component::Position, component::Sprite>();
		auto animatedIds = Ecs::filter<component::AnimatedSprite, component::Position>();

		auto &sprites = Ecs::getConponentMap<component::Sprite>();
		auto &positions = Ecs::getConponentMap<component::Position>();
		auto &animateds = Ecs::getConponentMap<component::AnimatedSprite>();

		auto window = graphical::Graphic::getWindow();

		for (auto id = ids.begin(); id != ids.end(); id++) {
			if (!sprites[*id].visible) {
				ids.erase(id);
				if (id != ids.begin())
					id--;
			}
		}
		for (auto id = animatedIds.begin(); id != animatedIds.end(); id++) {
			if (!animateds[*id].visible) {
				ids.erase(id);
				if (id != ids.begin())
					id--;
			}
		}

		std::sort (ids.begin(), ids.end(), [](ID one, ID two){ return (
			Ecs::getConponentMap<component::Sprite>()[one].layer <
				Ecs::getConponentMap<component::Sprite>()[two].layer); });

		std::sort (ids.begin(), ids.end(), [](ID one, ID two){ return (
			Ecs::getConponentMap<component::AnimatedSprite>()[one].layer <
			Ecs::getConponentMap<component::AnimatedSprite>()[two].layer); });

		auto sprite = ids.begin();
		auto animated = animatedIds.begin();
		while (sprite != ids.end() || animated != animatedIds.end()) {
			if (animated != animatedIds.end() && sprite != ids.end() && sprites[*sprite].layer > animateds[*animated].layer) {
				UpdateAnimatedSprite(animateds[*animated]);
				animateds[*animated].animation[animateds[*animated].frame].sprite->setPosition(positions[*animated].x, positions[*animated].y);
				window->draw(*animateds[*animated].animation[animateds[*animated].frame].sprite);
				animated++;
			} else if (sprite != ids.end() && animated != animatedIds.end() && animateds[*animated].layer > sprites[*sprite].layer) {
				sprites[*sprite].sprite->setPosition(positions[*sprite].x, positions[*sprite].y);
				window->draw(*sprites[*sprite].sprite);
				sprite++;
			} else {
				if (animated != animatedIds.end()) {
					UpdateAnimatedSprite(animateds[*animated]);
					animateds[*animated].animation[animateds[*animated].frame].sprite->setPosition(positions[*animated].x, positions[*animated].y);
					window->draw(*animateds[*animated].animation[animateds[*animated].frame].sprite);
					animated++;
				}
				if (sprite != ids.end()) {
					sprites[*sprite].sprite->setPosition(positions[*sprite].x, positions[*sprite].y);
					window->draw(*sprites[*sprite].sprite);
					sprite++;
				}
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