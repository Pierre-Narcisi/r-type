/*
** EPITECH PROJECT, 2021
** server
** File description:
** Created by seb,
*/

#include "Controls.hpp"
#include "ecs/Ecs.hpp"
#include "component/control/Keyboard.hpp"
#include "component/control/Mouse.hpp"
#include "component/control/DeplacementKeyBoard.hpp"
#include "component/control/DeplacementMouse.hpp"
#include "component/control/LazyDeplacementMouse.hpp"
#include "component/physic/Position.hpp"
#include "component/physic/Speed.hpp"

namespace ecs { namespace system {

	void Controls::UpdateKeyboards() {
		auto &keyboards = ecs::Ecs::getComponentMap<component::Keyboard>();

		for (auto &keyboard : keyboards) {
			for (auto it = keyboard.second.keyMap.begin(); it != keyboard.second.keyMap.end(); it++) {
				if (keyboard.second.keyMap[it->first].second)
					keyboard.second.keyMap[it->first].second(keyboard.first);
			}
		}
	}

	void Controls::UpdateMouses() {
		auto &mouses = ecs::Ecs::getComponentMap<component::Mouse>();

		for (auto &mouse : mouses) {
			for (auto it = mouse.second.mouseMap.begin(); it != mouse.second.mouseMap.end(); it++) {
				if (mouse.second.mouseMap[it->first].second)
					mouse.second.mouseMap[it->first].second(mouse.first);
			}
		}
	}

	void Controls::UpdateDeplacement() {
		auto deplacements = ecs::Ecs::filter<component::Keyboard, component::DeplacementKeyBoard, component::Speed>();
		float time;

		for (auto tomove : deplacements) {
			auto &keyB = ecs::Ecs::getComponentMap<component::Keyboard>()[tomove];
			auto &dep = ecs::Ecs::getComponentMap<component::DeplacementKeyBoard>()[tomove];
			core::Vector2<float> deplacement(0.f, 0.f);

			if (keyB.keyMap[dep.forward].first)
				deplacement.y = -dep.speed;
			else if (keyB.keyMap[dep.backward].first)
				deplacement.y = dep.speed;
			if (keyB.keyMap[dep.left].first)
				deplacement.x = -dep.speed;
			else if (keyB.keyMap[dep.right].first)
				deplacement.x = dep.speed;

			if (keyB.keyMap[dep.forward].first && keyB.keyMap[dep.left].first) {
				deplacement.y = static_cast<float>(-(dep.speed * 0.7071));
				deplacement.x = static_cast<float>(-(dep.speed * 0.7071));
			}
			if (keyB.keyMap[dep.forward].first && keyB.keyMap[dep.right].first) {
				deplacement.y = static_cast<float>(-(dep.speed * 0.7071));
				deplacement.x = static_cast<float>((dep.speed * 0.7071));
			}
			if (keyB.keyMap[dep.backward].first && keyB.keyMap[dep.left].first) {
				deplacement.y = static_cast<float>((dep.speed * 0.7071));
				deplacement.x = static_cast<float>(-(dep.speed * 0.7071));
			}
			if (keyB.keyMap[dep.backward].first && keyB.keyMap[dep.right].first) {
				deplacement.y = static_cast<float>((dep.speed * 0.7071));
				deplacement.x = static_cast<float>((dep.speed * 0.7071));
			}
			time = static_cast<float>(ecs::core::Time::get(TimeUnit::MicroSeconds) - dep.lastMove);
			ecs::Ecs::getComponentMap<component::Speed>()[tomove].x = time / 1000000.f * deplacement.x;
			ecs::Ecs::getComponentMap<component::Speed>()[tomove].y = time / 1000000.f * deplacement.y;
			dep.lastMove = ecs::core::Time::get(TimeUnit::MicroSeconds);
		}

		auto mouses = ecs::Ecs::filter<component::Mouse, component::Speed, component::DeplacementMouse, component::Position>();
		auto &mouseMap = ecs::Ecs::getComponentMap<component::Mouse>();
		auto &mouseDepMap = ecs::Ecs::getComponentMap<component::DeplacementMouse>();
		auto &speedMap = ecs::Ecs::getComponentMap<component::Speed>();
		auto &posMap = ecs::Ecs::getComponentMap<component::Position>();
		for (auto mouse : mouses) {
			mouseDepMap[mouse].lastPosition.x = (int)posMap[mouse].x;
			mouseDepMap[mouse].lastPosition.y = (int)posMap[mouse].y;
			if (!(mouseMap[mouse].position == mouseDepMap[mouse].lastPosition)) {
				if (abs(mouseMap[mouse].position.x - mouseDepMap[mouse].lastPosition.x) + abs(mouseMap[mouse].position.y - mouseDepMap[mouse].lastPosition.y) < mouseDepMap[mouse].speed) {
					speedMap[mouse].x = (float)mouseMap[mouse].position.x - mouseDepMap[mouse].lastPosition.x;
					speedMap[mouse].y = (float)mouseMap[mouse].position.y - mouseDepMap[mouse].lastPosition.y;
				} else {
					auto total = abs(mouseMap[mouse].position.x - mouseDepMap[mouse].lastPosition.x) + abs(mouseMap[mouse].position.y - mouseDepMap[mouse].lastPosition.y);
					speedMap[mouse].x = (float)mouseDepMap[mouse].speed * (mouseMap[mouse].position.x - mouseDepMap[mouse].lastPosition.x) / total;
					speedMap[mouse].y = (float)mouseDepMap[mouse].speed * (mouseMap[mouse].position.y - mouseDepMap[mouse].lastPosition.y) / total;
				}
			} else {
				speedMap[mouse].x = 0.f;
				speedMap[mouse].y = 0.f;
			}
			time = static_cast<float>(ecs::core::Time::get(TimeUnit::MicroSeconds) - mouseDepMap[mouse].lastMove);
			speedMap[mouse].x = time / 1000000.f * speedMap[mouse].x;
			speedMap[mouse].y = time / 1000000.f * speedMap[mouse].y;
			mouseDepMap[mouse] = time;
		}

		auto lazys = ecs::Ecs::filter<ecs::component::Speed, ecs::component::LazyDeplacementMouse, ecs::component::Mouse>();

		for(auto id : lazys) {
			posMap[id].x = (float)mouseMap[id].position.x;
			posMap[id].y = (float)mouseMap[id].position.y;
		}
	}

}}